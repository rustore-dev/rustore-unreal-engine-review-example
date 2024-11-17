// Copyright Epic Games, Inc. All Rights Reserved.

#include "URuStoreReviewManager.h"
#include "URuStoreCore.h"
#include "ReviewResponseListenerImpl.h"

using namespace RuStoreSDK;

const FString URuStoreReviewManager::PluginVersion = "7.0.0";
URuStoreReviewManager* URuStoreReviewManager::_instance = nullptr;
bool URuStoreReviewManager::_bIsInstanceInitialized = false;

bool URuStoreReviewManager::GetIsInitialized() { return bIsInitialized; }

URuStoreReviewManager* URuStoreReviewManager::Instance()
{
    if (!_bIsInstanceInitialized)
    {
        _bIsInstanceInitialized = true;
        _instance = NewObject<URuStoreReviewManager>(GetTransientPackage());
    }

    return _instance;
}

void URuStoreReviewManager::SetAllowNativeErrorHandling(bool value)
{
    if (!URuStoreCore::IsPlatformSupported()) return;
    if (bIsInitialized) return;

    _bAllowNativeErrorHandling = value;
    _clientWrapper->CallVoid("setErrorHandling", value);
}

bool URuStoreReviewManager::Init()
{
    if (!URuStoreCore::IsPlatformSupported()) return false;
    if (bIsInitialized) return false;

    _instance->AddToRoot();

    URuStoreCore::Instance()->Init();

    auto clientJavaClass = MakeShared<AndroidJavaClass>("ru/rustore/unitysdk/review/RuStoreUnityReviewManager");
    _clientWrapper = clientJavaClass->GetStaticAJObject("INSTANCE");
    _clientWrapper->CallVoid("init", FString("unreal"));

    return bIsInitialized = true;
}

void URuStoreReviewManager::Dispose()
{
    if (bIsInitialized)
    {
        bIsInitialized = false;
        ListenerRemoveAll();
        delete _clientWrapper;
        _instance->RemoveFromRoot();
    }
}

void URuStoreReviewManager::ConditionalBeginDestroy()
{
    Super::ConditionalBeginDestroy();

    Dispose();
    if (_bIsInstanceInitialized) _bIsInstanceInitialized = false;
}

long URuStoreReviewManager::RequestReviewFlow(TFunction<void(long)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!bIsInitialized) return 0;

    auto listener = ListenerBind(new ReviewResponseListenerImpl(onSuccess, onFailure, [this](RuStoreListener* item) { ListenerUnbind(item); }));
    _clientWrapper->CallVoid("requestReviewFlow", listener->GetJWrapper());

    return listener->GetId();
}

long URuStoreReviewManager::LaunchReviewFlow(TFunction<void(long)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!bIsInitialized) return 0;

    auto listener = ListenerBind(new ReviewResponseListenerImpl(onSuccess, onFailure, [this](RuStoreListener* item) { ListenerUnbind(item); }));
    _clientWrapper->CallVoid("launchReviewFlow", listener->GetJWrapper());

    return listener->GetId();
}

void URuStoreReviewManager::RequestReviewFlow(int64& requestId)
{
    requestId = RequestReviewFlow(
        [this](long requestId) {
            OnRequestReviewFlowResponse.Broadcast(requestId);
        },
        [this](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            OnRequestReviewFlowError.Broadcast(requestId, *error);
        }
    );
}

void URuStoreReviewManager::LaunchReviewFlow(int64& requestId)
{
    requestId = LaunchReviewFlow(
        [this](long requestId) {
            OnLaunchReviewFlowResponse.Broadcast(requestId);
        },
        [this](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            OnLaunchReviewFlowError.Broadcast(requestId, *error);
        }
    );
}
