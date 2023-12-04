// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "URuStoreReviewManager.h"
#include "ULaunchReviewFlowNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLaunchReviewFlowPin, FURuStoreError, error);

UCLASS()
class RUSTOREREVIEW_API ULaunchReviewFlowNode : public UBlueprintAsyncActionBase
{
    GENERATED_UCLASS_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FLaunchReviewFlowPin Success;

    UPROPERTY(BlueprintAssignable)
    FLaunchReviewFlowPin Failure;

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "RuStore Review Manager")
    static ULaunchReviewFlowNode* LaunchReviewFlowAsync(URuStoreReviewManager* target);
};
