#pragma once

#include "GenericPlatformNuiUtils.h"
#include "IOSNuiUtils.h"
#include "AndroidNuiUtils.h"

#if PLATFORM_ANDROID
	typedef FAndroidNuiUtils FNuiUtils;
#elif PLATFORM_IOS
	typedef FIOSNuiUtils FNuiUtils;
#else
	typedef FGenericPlatformNuiUtils FNuiUtils;
#endif
