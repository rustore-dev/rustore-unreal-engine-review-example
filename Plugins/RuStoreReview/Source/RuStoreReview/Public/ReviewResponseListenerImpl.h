#pragma once

#include "SimpleResponseListener.h"

class RUSTOREREVIEW_API ReviewResponseListenerImpl : public SimpleResponseListener
{
public:
    ReviewResponseListenerImpl(
        TFunction<void(long, FURuStoreError*)> onFailure,
        TFunction<void(long)> onSuccess,
        TFunction<void(RuStoreListener*)> onFinish
    ) : SimpleResponseListener("com/Plugins/RuStoreReview/ReviewResponseListenerWrapper", "ru/rustore/unitysdk/review/ReviewResponseListener", onFailure, onSuccess, onFinish)
    {
    }

    virtual ~ReviewResponseListenerImpl();
};
