#include "ReviewResponseListenerImpl.h"
#include "AndroidJavaObjectFactory.h"

#if PLATFORM_ANDROID
extern "C"
{
    JNIEXPORT void JNICALL Java_ru_rustore_unrealsdk_review_wrappers_ReviewResponseListenerWrapper_NativeOnFailure(JNIEnv*, jobject, jlong pointer, jthrowable throwable)
    {
        auto obj = RuStoreSDK::AndroidJavaObjectFactory::CreateFromThrowable(throwable);

        auto castobj = reinterpret_cast<RuStoreSDK::ReviewResponseListenerImpl*>(pointer);
        castobj->OnFailure(obj);
    }

    JNIEXPORT void JNICALL Java_ru_rustore_unrealsdk_review_wrappers_ReviewResponseListenerWrapper_NativeOnSuccess(JNIEnv*, jobject, jlong pointer)
    {
        auto castobj = reinterpret_cast<RuStoreSDK::ReviewResponseListenerImpl*>(pointer);
        castobj->OnSuccess();
    }
}
#endif
