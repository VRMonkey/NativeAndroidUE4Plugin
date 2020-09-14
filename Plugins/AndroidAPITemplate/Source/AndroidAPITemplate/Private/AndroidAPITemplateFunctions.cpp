// Copyright (c) 2018 Isara Technologies. All Rights Reserved.
#include "AndroidAPITemplateFunctions.h"
#include "AndroidAPITemplatePrivatePCH.h"

#if PLATFORM_ANDROID

#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"

#define INIT_JAVA_METHOD(name, signature) \
if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true)) { \
	name = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, #name, signature, false); \
	check(name != NULL); \
} else { \
	check(0); \
}

#define DECLARE_JAVA_METHOD(name) \
static jmethodID name = NULL;

DECLARE_JAVA_METHOD(AndroidThunkJava_AndroidAPI_ShowToast);	
DECLARE_JAVA_METHOD(AndroidThunkJava_AndroidAPI_GetLastLightMeasure); // Here goes the name of the method in the Java side

void UAndroidAPITemplateFunctions::InitJavaFunctions()
{
	// Same here, but we add the Java signature (the type of the parameters is between the parameters, and the return type is added at the end,
	// here the return type is V for "void")
	// More details here about Java signatures: http://www.rgagnon.com/javadetails/java-0286.html
	INIT_JAVA_METHOD(AndroidThunkJava_AndroidAPI_ShowToast, "(Ljava/lang/String;)V");
	INIT_JAVA_METHOD(AndroidThunkJava_AndroidAPI_GetLastLightMeasure, "([F)V");
}
#undef DECLARE_JAVA_METHOD
#undef INIT_JAVA_METHOD

#endif


void UAndroidAPITemplateFunctions::AndroidAPITemplate_ShowToast(const FString& Content)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true))
	{
		// First step, we convert the FString (UE4) parameter to a JNI parameter that will hold a String
		jstring JavaString = Env->NewStringUTF(TCHAR_TO_UTF8(*Content));

		// Then we call the method, we the Java String parameter
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_AndroidAPI_ShowToast, JavaString);
	}
#endif
}

float UAndroidAPITemplateFunctions::AndroidAPITemplate_GetLastLightMeasure()
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv(true))
	{
		jfloatArray Result = Env->NewFloatArray(1);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, AndroidThunkJava_AndroidAPI_GetLastLightMeasure, Result);

		jfloat* ResultArr = Env->GetFloatArrayElements(Result, 0);

		const float ResultFloat = ResultArr[0];

		Env->DeleteLocalRef(Result);

		return ResultFloat;
	}
	else
	{
		UE_LOG(LogAndroid, Warning, TEXT("ERROR: Could not get Java ENV\n"));

		return 0;
	}
#else
	return 0;
#endif
}