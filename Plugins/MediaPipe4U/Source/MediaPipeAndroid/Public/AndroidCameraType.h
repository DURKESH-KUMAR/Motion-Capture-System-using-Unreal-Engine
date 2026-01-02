// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "CoreMinimal.h"
#include "AndroidCameraType.generated.h"


UENUM(BlueprintType)
enum class EAndroidCameraType : uint8
{
	FrontLens = 0,
	BackLens = 1
};
