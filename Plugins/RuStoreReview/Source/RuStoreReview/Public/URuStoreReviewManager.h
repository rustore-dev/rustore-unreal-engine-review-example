#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "AndroidJavaClass.h"
// Copyright Epic Games, Inc. All Rights Reserved.

#include "FURuStoreError.h"
#include "RuStoreListener.h"
#include "URuStoreReviewManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRequestReviewFlowErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRequestReviewFlowResponseDelegate, int64, requestId);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLaunchReviewFlowErrorDelegate, int64, requestId, FURuStoreError, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLaunchReviewFlowResponseDelegate, int64, requestId);

using namespace RuStoreSDK;

UCLASS(Blueprintable)
class RUSTOREREVIEW_API URuStoreReviewManager : public UObject, public RuStoreListenerContainer
{
	GENERATED_BODY()

private:
    static URuStoreReviewManager* _instance;
    static bool _bIsInstanceInitialized;

    bool bIsInitialized = false;
    bool _bAllowNativeErrorHandling = false;
    AndroidJavaObject* _clientWrapper = nullptr;

public:
    static const FString PluginVersion;

    UFUNCTION(BlueprintCallable, Category = "RuStore Review Manager")
    bool getIsInitialized();

    UFUNCTION(BlueprintCallable, Category = "RuStore Review Manager")
    static URuStoreReviewManager* Instance();

	UFUNCTION(BlueprintCallable, Category = "RuStore Review Manager")
    void SetAllowNativeErrorHandling(bool value);

    UFUNCTION(BlueprintCallable, Category = "RuStore Review Manager")
    bool Init();

    UFUNCTION(BlueprintCallable, Category = "RuStore Review Manager")
    void Dispose();

    void ConditionalBeginDestroy();

    long RequestReviewFlow(TFunction<void(long)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);
    long LaunchReviewFlow(TFunction<void(long)> onSuccess, TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure);


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
