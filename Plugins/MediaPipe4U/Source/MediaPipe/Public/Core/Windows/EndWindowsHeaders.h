// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once

#if PLATFORM_WINDOWS

#include "Misc/EngineVersionComparison.h"

#if UE_VERSION_OLDER_THAN(5,1,0)
#include "Windows/PostWindowsApi.h"
#endif

#include "Windows/HideWindowsPlatformTypes.h"

#endif
