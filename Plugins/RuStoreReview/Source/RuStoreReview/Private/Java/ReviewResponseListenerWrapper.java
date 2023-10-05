// Copyright Epic Games, Inc. All Rights Reserved.

package com.Plugins.RuStoreReview;

import com.Plugins.RuStoreCore.IRuStoreListener;
import ru.rustore.unitysdk.review.ReviewResponseListener;

public class ReviewResponseListenerWrapper implements IRuStoreListener, ReviewResponseListener
{
    private Object mutex = new Object();
    private long cppPointer;

    private native void NativeOnFailure(long pointer, Throwable throwable);
    private native void NativeOnSuccess(long pointer);

    public ReviewResponseListenerWrapper(long cppPointer) {
        this.cppPointer = cppPointer;
    }

    @Override
    public void OnFailure(Throwable throwable) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                NativeOnFailure(cppPointer, throwable);
            }
        }
    }

    @Override
    public void OnSuccess() {
        synchronized (mutex) {
            if (cppPointer != 0) {
                NativeOnSuccess(cppPointer);
            }
        }
    }

    public void DisposeCppPointer() {
        synchronized (mutex) {
            cppPointer = 0;
        }
    }
}
