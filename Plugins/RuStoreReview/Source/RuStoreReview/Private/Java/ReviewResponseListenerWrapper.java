package com.Plugins.RuStoreReview;

import com.Plugins.RuStoreCore.IResponseListenerWrapper;
import ru.rustore.unitysdk.review.ReviewResponseListener;

import android.util.Log;

public class ReviewResponseListenerWrapper implements IResponseListenerWrapper, ReviewResponseListener
{
    private Object mutex = new Object();
    private long cppPointer = 0;

    private native void NativeOnFailure(long pointer, Throwable throwable);
    private native void NativeOnSuccess(long pointer);

    public ReviewResponseListenerWrapper(long cppPointer) {
        this.cppPointer = cppPointer;
    }

    @Override
    public void OnFailure(Throwable throwable) {
        synchronized (mutex) {
            if (cppPointer != 0) {
                Log.e("rustore", "ReviewResponse: Error message");
                NativeOnFailure(cppPointer, throwable);
            }
        }
    }

    @Override
    public void OnSuccess() {
        synchronized (mutex) {
            if (cppPointer != 0) {
                Log.e("rustore", "ReviewResponse: Success message");
                NativeOnSuccess(cppPointer);
            }
        }
    }

    public void DisposeCppPointer() {
        synchronized (mutex) {
            Log.e("rustore", "FeatureAvailabilityResult: Dispose pointer");
            cppPointer = 0;
        }
    }
}
