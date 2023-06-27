#include "ReviewResponseListenerImpl.h"

ReviewResponseListenerImpl::~ReviewResponseListenerImpl()
{
    FString tag = "rustore_debug";
    FString msg = "~ReviewResponseListenerImpl";
#if PLATFORM_ANDROID
    __android_log_write(ANDROID_LOG_INFO, TCHAR_TO_UTF8(*tag), TCHAR_TO_UTF8(*msg));
#endif
}

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_com_Plugins_RuStoreReview_ReviewResponseListenerWrapper_NativeOnFailure(JNIEnv*, jobject, jlong pointer, jthrowable throwable)
    {
        auto obj = new AndroidJavaObject(throwable);
        obj->UpdateToGlobalRef();

        auto castobj = reinterpret_cast<SimpleResponseListener*>(pointer);
        castobj->OnFailure(obj);
    }

    JNIEXPORT void JNICALL Java_com_Plugins_RuStoreReview_ReviewResponseListenerWrapper_NativeOnSuccess(JNIEnv*, jobject, jlong pointer)
    {
        auto castobj = reinterpret_cast<SimpleResponseListener*>(pointer);
        castobj->OnSuccess();
    }
}
#endif
