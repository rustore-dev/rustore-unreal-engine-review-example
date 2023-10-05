// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SimpleResponseListener.h"

namespace RuStoreSDK
{
    class RUSTOREREVIEW_API ReviewResponseListenerImpl : public SimpleResponseListener
    {
    public:
        ReviewResponseListenerImpl(
            TFunction<void(long)> onSuccess,
            TFunction<void(long, TSharedPtr<FURuStoreError, ESPMode::ThreadSafe>)> onFailure,
            TFunction<void(RuStoreListener*)> onFinish
        ) : SimpleResponseListener("com/Plugins/RuStoreReview/ReviewResponseListenerWrapper", "ru/rustore/unitysdk/review/ReviewResponseListener", onSuccess, onFailure, onFinish)
        {
        }
    };
}
