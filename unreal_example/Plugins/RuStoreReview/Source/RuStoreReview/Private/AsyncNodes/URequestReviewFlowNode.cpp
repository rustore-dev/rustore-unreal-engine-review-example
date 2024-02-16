// Copyright Epic Games, Inc. All Rights Reserved.

#include "URequestReviewFlowNode.h"

using namespace RuStoreSDK;

URequestReviewFlowNode::URequestReviewFlowNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

URequestReviewFlowNode* URequestReviewFlowNode::RequestReviewFlowAsync(URuStoreReviewManager* target)
{
    auto node = NewObject<URequestReviewFlowNode>(GetTransientPackage());
    
    target->RequestReviewFlow(
        [node](long requestId) {
            node->Success.Broadcast(FURuStoreError());
        },
        [node](long requestId, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe> error) {
            node->Failure.Broadcast(*error);
        }
    );

    return node;
}
