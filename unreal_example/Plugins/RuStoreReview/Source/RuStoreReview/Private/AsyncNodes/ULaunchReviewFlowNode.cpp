// Copyright Epic Games, Inc. All Rights Reserved.

#include "ULaunchReviewFlowNode.h"

using namespace RuStoreSDK;

ULaunchReviewFlowNode::ULaunchReviewFlowNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

ULaunchReviewFlowNode* ULaunchReviewFlowNode::LaunchReviewFlowAsync(URuStoreReviewManager* target)
{
    auto node = NewObject<ULaunchReviewFlowNode>(GetTransientPackage());
    
    target->LaunchReviewFlow(
        [node](long requestId) {
            node->Success.Broadcast(FURuStoreError());
        },
        [node](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            node->Failure.Broadcast(*error);
        }
    );

    return node;
}
