#include "URuStoreReviewManager.h"
#include "URuStoreCore.h"
#include "ReviewResponseListenerImpl.h"

using namespace std;

const FString URuStoreReviewManager::PluginVersion = "0.1";

URuStoreReviewManager* URuStoreReviewManager::_instance = nullptr;
bool URuStoreReviewManager::_isInstanceInitialized = false;

bool URuStoreReviewManager::getIsInitialized() { return isInitialized; }

URuStoreReviewManager* URuStoreReviewManager::Instance()
{
    if (!_isInstanceInitialized)
    {
        _isInstanceInitialized = true;
        _instance = NewObject<URuStoreReviewManager>(GetTransientPackage());
    }

    return _instance;
}

void URuStoreReviewManager::SetAllowNativeErrorHandling(bool value)
{
    _allowNativeErrorHandling = value;

    if (isInitialized)
    {
        _clientWrapper->CallVoid("setErrorHandling", value);
    }
}

URuStoreReviewManager::URuStoreReviewManager()
{
}

URuStoreReviewManager::~URuStoreReviewManager()
{
}

bool URuStoreReviewManager::Init()
{
    if (!URuStoreCore::IsPlatformSupported()) return false;
    if (isInitialized) return false;

    _instance->AddToRoot();

    URuStoreCore::Instance()->Init();

    AndroidJavaClass* clientJavaClass = new AndroidJavaClass("ru/rustore/unitysdk/review/RuStoreUnityReviewManager");
    _clientWrapper = clientJavaClass->GetStaticAJObject("INSTANCE");
    _clientWrapper->CallVoid("init");

    isInitialized = true;

    return isInitialized;
}

void URuStoreReviewManager::Dispose()
{
    if (isInitialized)
    {
        isInitialized = false;
        ListenerRemoveAll();
        delete _clientWrapper;
        _instance->RemoveFromRoot();
    }
}

void URuStoreReviewManager::BeginDestroy()
{
    Super::BeginDestroy();

    Dispose();
    if (_isInstanceInitialized) _isInstanceInitialized = false;
}

long URuStoreReviewManager::RequestReviewFlow(TFunction<void(long, FURuStoreError*)> onFailure, TFunction<void(long)> onSuccess)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!isInitialized) return 0;

    auto listener = new ReviewResponseListenerImpl(onFailure, onSuccess, [this](RuStoreListener* item) { ListenerUnbind(item); });
    ListenerBind((RuStoreListener*)listener);
    _clientWrapper->CallVoid("requestReviewFlow", listener->GetJWrapper());

    return listener->GetId();
}

long URuStoreReviewManager::LaunchReviewFlow(TFunction<void(long, FURuStoreError*)> onFailure, TFunction<void(long)> onSuccess)
{
    if (!URuStoreCore::IsPlatformSupported(onFailure)) return 0;
    if (!isInitialized) return 0;

    auto listener = new ReviewResponseListenerImpl(onFailure, onSuccess, [this](RuStoreListener* item) { ListenerUnbind(item); });
    ListenerBind((RuStoreListener*)listener);
    _clientWrapper->CallVoid("launchReviewFlow", listener->GetJWrapper());

    return listener->GetId();
}

void URuStoreReviewManager::RequestReviewFlow(int64& requestId)
{
    requestId = RequestReviewFlow(
        [this](long requestId, FURuStoreError* error) {
            OnRequestReviewFlowError.Broadcast(requestId, *error);
        },
        [this](long requestId) {
            OnRequestReviewFlowResponse.Broadcast(requestId);
        }
    );
}

void URuStoreReviewManager::LaunchReviewFlow(int64& requestId)
{
    requestId = LaunchReviewFlow(
        [this](long requestId, FURuStoreError* error) {
            OnLaunchReviewFlowError.Broadcast(requestId, *error);
        },
        [this](long requestId) {
            OnLaunchReviewFlowResponse.Broadcast(requestId);
        }
    );
}
