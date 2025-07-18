// Copyright Epic Games, Inc. All Rights Reserved.

#include "URuStoreCore.h"
#include "AndroidJavaClass.h"
#include "JavaActivity.h"
#include "JavaApplication.h"

const FString URuStoreCore::PluginVersion = "9.1.0";
URuStoreCore* URuStoreCore::_instance = nullptr;
bool URuStoreCore::_bIsInstanceInitialized = false;

bool URuStoreCore::GetIsInitialized() { return bIsInitialized; }

URuStoreCore* URuStoreCore::Instance()
{
    if (!_bIsInstanceInitialized)
    {
        _bIsInstanceInitialized = true;
        _instance = NewObject<URuStoreCore>(GetTransientPackage());
    }
    return _instance;
}

bool URuStoreCore::Init()
{
    if (!URuStoreCore::IsPlatformSupported()) return false;
    if (bIsInitialized) return false;

    _instance->AddToRoot();

    unrealPlayer = new UnrealPlayerImpl();

    auto playerProviderJavaClass = MakeShared<AndroidJavaClass>("ru/rustore/unitysdk/core/PlayerProvider");
    _playerProviderWrapper = playerProviderJavaClass->GetStaticAJObject("INSTANCE");
    _playerProviderWrapper->CallVoid("setExternalProvider", unrealPlayer->GetJWrapper());

    auto clientJavaClass = MakeShared<AndroidJavaClass>("ru/rustore/unitysdk/core/RuStoreUnityCoreClient");
    _clientWrapper = clientJavaClass->GetStaticAJObject("INSTANCE");

    bIsInitialized = true;

    return bIsInitialized;
}

void URuStoreCore::Dispose()
{
    if (bIsInitialized)
    {
        bIsInitialized = false;
        delete _clientWrapper;
        delete _playerProviderWrapper;
        delete unrealPlayer;
        _instance->RemoveFromRoot();
    }
}

void URuStoreCore::ConditionalBeginDestroy()
{
    Super::ConditionalBeginDestroy();

    Dispose();
    if (_bIsInstanceInitialized) _bIsInstanceInitialized = false;
}

bool URuStoreCore::IsPlatformSupported()
{
#if PLATFORM_ANDROID
    return true;
#endif
    return false;
}

bool URuStoreCore::IsPlatformSupported(TFunction<void(long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure)
{
    if (IsPlatformSupported()) return true;

    auto error = MakeShared<FURuStoreError, ESPMode::ThreadSafe>();
    error->name = "RuStore Error";
    error->description = "Unsupported platform";
    
    onFailure(0, error);
    
    return false;
}

void URuStoreCore::ShowToast(FString message)
{
    auto javaClass = MakeShared<AndroidJavaClass>("com/Plugins/RuStoreCore/RuStoreCoreUtils");
    auto activity = MakeShared<JavaActivity>();

    javaClass->CallStaticVoid("showToast", &activity.Get(), message);
}

void URuStoreCore::LogVerbose(FString tag, FString message)
{
    _LogVerbose(tag, message);
}

void URuStoreCore::LogDebug(FString tag, FString message)
{
    _LogDebug(tag, message);
}

void URuStoreCore::LogInfo(FString tag, FString message)
{
    _LogInfo(tag, message);
}

void URuStoreCore::LogWarn(FString tag, FString message)
{
    _LogWarn(tag, message);
}

void URuStoreCore::LogError(FString tag, FString message)
{
    _LogError(tag, message);
}

bool URuStoreCore::CompareId(int64 A, int64 B)
{
    return (A == B && A != 0);
}

void URuStoreCore::CopyToClipboard(FString text)
{
    auto javaClass = MakeShared<AndroidJavaClass>("com/Plugins/RuStoreCore/RuStoreCoreUtils");
    auto activity = MakeShared<JavaActivity>();

    javaClass->CallStaticVoid("CopyToClipboard", &activity.Get(), text);
}

void URuStoreCore::GetFromClipboard(FString& text)
{
    auto javaClass = MakeShared<AndroidJavaClass>("com/Plugins/RuStoreCore/RuStoreCoreUtils");
    auto activity = MakeShared<JavaActivity>();

    text = javaClass->CallStaticFString("GetFromClipboard", &activity.Get());
}

void URuStoreCore::GetStringResources(FString name, FString& value)
{
    auto javaClass = MakeShared<AndroidJavaClass>("com/Plugins/RuStoreCore/RuStoreCoreUtils");
    auto application = MakeShared<JavaApplication>();

    value = javaClass->CallStaticFString("GetStringResources", &application.Get(), name);
}

void URuStoreCore::GetIntResources(FString name, int& value)
{
    auto javaClass = MakeShared<AndroidJavaClass>("com/Plugins/RuStoreCore/RuStoreCoreUtils");
    auto application = MakeShared<JavaApplication>();

    value = javaClass->CallStaticInt("GetIntResources", &application.Get(), name);
}

FString URuStoreCore::GetStringSharedPreferences(FString storageName, FString key, FString defaultValue)
{
    auto javaClass = MakeShared<AndroidJavaClass>("com/Plugins/RuStoreCore/RuStoreCoreUtils");
    auto application = MakeShared<JavaApplication>();

    return javaClass->CallStaticFString("GetStringSharedPreferences", &application.Get(), storageName, key, defaultValue);
}

int URuStoreCore::GetIntSharedPreferences(FString storageName, FString key, int defaultValue)
{
    auto javaClass = MakeShared<AndroidJavaClass>("com/Plugins/RuStoreCore/RuStoreCoreUtils");
    auto application = MakeShared<JavaApplication>();

    return javaClass->CallStaticInt("GetIntSharedPreferences", &application.Get(), storageName, key, defaultValue);
}

void URuStoreCore::SetStringSharedPreferences(FString storageName, FString key, FString value)
{
    auto javaClass = MakeShared<AndroidJavaClass>("com/Plugins/RuStoreCore/RuStoreCoreUtils");
    auto application = MakeShared<JavaApplication>();
    javaClass->CallStaticVoid("SetStringSharedPreferences", &application.Get(), storageName, key, value);
}

void URuStoreCore::SetIntSharedPreferences(FString storageName, FString key, int value)
{
    auto javaClass = MakeShared<AndroidJavaClass>("com/Plugins/RuStoreCore/RuStoreCoreUtils");
    auto application = MakeShared<JavaApplication>();
    javaClass->CallStaticVoid("SetIntSharedPreferences", &application.Get(), storageName, key, value);
}

void URuStoreCore::RestartAndroidApp() {
    auto javaClass = MakeShared<AndroidJavaClass>("com/Plugins/RuStoreCore/RuStoreCoreUtils");
    auto application = MakeShared<JavaApplication>();

    return javaClass->CallStaticVoid("RestartAndroidApp", &application.Get());
}

bool URuStoreCore::IsRuStoreInstalled() {
    auto activity = MakeShared<JavaActivity>();

    return _clientWrapper->CallBool("isRuStoreInstalled", &activity.Get());
}

void URuStoreCore::OpenRuStoreDownloadInstruction() {
    auto activity = MakeShared<JavaActivity>();
    _clientWrapper->CallVoid("openRuStoreDownloadInstruction", &activity.Get());
}

void URuStoreCore::OpenRuStore() {
    auto activity = MakeShared<JavaActivity>();
    _clientWrapper->CallVoid("openRuStore", &activity.Get());
}

void URuStoreCore::OpenRuStoreAuthorization() {
    auto activity = MakeShared<JavaActivity>();
    _clientWrapper->CallVoid("openRuStoreAuthorization", &activity.Get());
}
