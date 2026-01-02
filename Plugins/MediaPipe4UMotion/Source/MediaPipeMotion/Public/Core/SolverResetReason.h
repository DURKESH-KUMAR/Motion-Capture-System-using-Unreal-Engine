// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "CoreMinimal.h"
#include "SolverResetReason.generated.h"

UENUM(BlueprintType)
enum class ESolverResetReason : uint8
{
	MediaPipeStart,
	MediaPipeStop,
	CacheBones,
	Calibration,
	PrepareSolving,
	StaticImageRefresh
};
