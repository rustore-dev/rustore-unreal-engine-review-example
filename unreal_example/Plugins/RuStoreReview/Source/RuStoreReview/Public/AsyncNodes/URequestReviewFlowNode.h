// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "URuStoreReviewManager.h"
#include "URequestReviewFlowNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRequestReviewFlowPin, FURuStoreError, error);

UCLASS()
class RUSTOREREVIEW_API URequestReviewFlowNode : public UBlueprintAsyncActionBase
{
    GENERATED_UCLASS_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FRequestReviewFlowPin Success;

    UPROPERTY(BlueprintAssignable)
    FRequestReviewFlowPin Failure;

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "RuStore Review Manager")
    static URequestReviewFlowNode* RequestReviewFlowAsync(URuStoreReviewManager* target);
};
