// Fill out your copyright notice in the Description page of Project Settings.


#include "UAndroidHelper.h"

#if PLATFORM_ANDROID
#include <../../../Launch/Public/Android/AndroidJNI.h>
#include <Android/AndroidApplication.h>
#include <Android/AndroidJava.h>
#endif

void UAndroidHelper::OpenDeeplink(FString url)
{
#if PLATFORM_ANDROID
    if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
    {
        jclass classUri = env->FindClass("android/net/Uri");
        jmethodID methodParse = env->GetStaticMethodID(classUri, "parse", "(Ljava/lang/String;)Landroid/net/Uri;");
        jstring jUrl = env->NewStringUTF(TCHAR_TO_UTF8(*url));
        jobject jUri = env->CallStaticObjectMethod(classUri, methodParse, jUrl);

        jmethodID methodStartActivity = env->GetMethodID(FJavaWrapper::GameActivityClassID, "startActivity", "(Landroid/content/Intent;)V");
        jstring jActionView = env->NewStringUTF("android.intent.action.VIEW");

        jclass classIntent = env->FindClass("android/content/Intent");
        jmethodID methodIntentInit = env->GetMethodID(classIntent, "<init>", "(Ljava/lang/String;Landroid/net/Uri;)V");
        jmethodID methodAddFlags = env->GetMethodID(classIntent, "addFlags", "(I)Landroid/content/Intent;");
        jobject jIntent = env->NewObject(classIntent, methodIntentInit, jActionView, jUri);

        const int FLAG_ACTIVITY_NEW_TASK = 0x10000000;
        env->CallObjectMethod(jIntent, methodAddFlags, FLAG_ACTIVITY_NEW_TASK);
        env->CallVoidMethod(FAndroidApplication::GetGameActivityThis(), methodStartActivity, jIntent);

        env->DeleteLocalRef(jIntent);
        env->DeleteLocalRef(jActionView);
        env->DeleteLocalRef(jUri);
        env->DeleteLocalRef(jUrl);
    }
#endif
}
