// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once

#if PLATFORM_WINDOWS

#include "Misc/EngineVersionComparison.h"
#include "Windows/AllowWindowsPlatformTypes.h"

#if UE_VERSION_OLDER_THAN(5,1,0)
#include "Windows/PreWindowsApi.h"
#endif

#endif