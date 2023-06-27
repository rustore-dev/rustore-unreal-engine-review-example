#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/Interface.h"
#include "UObject/ScriptMacros.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include <functional>

#include "AndroidJavaObject.h"
#include "AndroidJavaClass.h"
#include "FURuStoreError.h"
#include "RuStoreListener.h"
#include "URuStoreReviewManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRequestReviewFlowErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRequestReviewFlowResponseDelegate, int64, requestId);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLaunchReviewFlowErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLaunchReviewFlowResponseDelegate, int64, requestId);

UCLASS(Blueprintable)
class RUSTOREREVIEW_API URuStoreReviewManager : public UObject, public RuStoreListenerContainer
{
	GENERATED_BODY()

private:
    static URuStoreReviewManager* _instance;
    static bool _isInstanceInitialized;

    bool _allowNativeErrorHandling;

    AndroidJavaObject* _clientWrapper;

public:
    static const FString PluginVersion;

    UPROPERTY(BlueprintReadOnly)
    bool isInitialized = false;

    UFUNCTION()
    bool getIsInitialized();

    UFUNCTION(BlueprintCallable, Category = "RuStore Review Manager")
    static URuStoreReviewManager* Instance();

    void SetAllowNativeErrorHandling(bool value);

    URuStoreReviewManager();
    ~URuStoreReviewManager();

    void BeginDestroy();

    UFUNCTION(BlueprintCallable, Category = "RuStore Review Manager")
    bool Init();

    UFUNCTION(BlueprintCallable, Category = "RuStore Review Manager")
    void Dispose();

    long RequestReviewFlow(TFunction<void(long, FURuStoreError*)> onFailure, TFunction<void(long)> onSuccess);
    long LaunchReviewFlow(TFunction<void(long, FURuStoreError*)> onFailure, TFunction<void(long)> onSuccess);


    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore Review Manager")
    void RequestReviewFlow(int64& requestId);

    UPROPERTY(BlueprintAssignable, Category = "RuStore Review Manager")
    FRequestReviewFlowErrorDelegate OnRequestReviewFlowError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Review Manager")
    FRequestReviewFlowResponseDelegate OnRequestReviewFlowResponse;


    // 
    UFUNCTION(BlueprintCallable, Category = "RuStore Review Manager")
    void LaunchReviewFlow(int64& requestId);

    UPROPERTY(BlueprintAssignable, Category = "RuStore Review Manager")
    FLaunchReviewFlowErrorDelegate OnLaunchReviewFlowError;

    UPROPERTY(BlueprintAssignable, Category = "RuStore Review Manager")
    FLaunchReviewFlowResponseDelegate OnLaunchReviewFlowResponse;
};
