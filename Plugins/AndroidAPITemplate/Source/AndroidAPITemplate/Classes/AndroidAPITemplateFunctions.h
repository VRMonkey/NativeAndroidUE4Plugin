// Copyright (c) 2018 Isara Technologies. All Rights Reserved.

#pragma once

#include "AndroidAPITemplateFunctions.generated.h"

UCLASS(NotBlueprintable)
class UAndroidAPITemplateFunctions : public UObject {
	GENERATED_BODY()
	
public:

#if PLATFORM_ANDROID
	static void InitJavaFunctions();
#endif

	/**
	 * Displays a toast text on the screen
	 */
	UFUNCTION(BlueprintCallable, meta = (Keywords = "AndroidAPI ", DisplayName = "Show Toast"), Category = "AndroidAPI")
		static void AndroidAPITemplate_ShowToast(const FString& Content);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Keywords = "AndroidAPI ", DisplayName = "Get Last Light Measure"), Category = "AndroidAPI")
		static float AndroidAPITemplate_GetLastLightMeasure();
};
