// Copyright (c) 2018 Isara Technologies. All Rights Reserved.

#include "AndroidAPITemplatePrivatePCH.h"

DEFINE_LOG_CATEGORY(LogAndroidAPITemplate);

#define LOCTEXT_NAMESPACE "AndroidAPITemplate"

class FAndroidAPITemplate : public IAndroidAPITemplate
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FAndroidAPITemplate, AndroidAPITemplate )

void FAndroidAPITemplate::StartupModule()
{
#if PLATFORM_ANDROID
	UAndroidAPITemplateFunctions::InitJavaFunctions();
#endif
}


void FAndroidAPITemplate::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
