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
        ) : SimpleResponseListener("ru/rustore/unrealsdk/review/wrappers/ReviewResponseListenerWrapper", "ru/rustore/unrealsdk/review/ReviewResponseListener", onSuccess, onFailure, onFinish)
        {
        }
    };
}
