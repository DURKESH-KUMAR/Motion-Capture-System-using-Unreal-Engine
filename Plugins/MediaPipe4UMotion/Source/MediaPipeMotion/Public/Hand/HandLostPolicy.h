// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "HandLostPolicy.generated.h"

UENUM(BlueprintType)
enum class EHandLostPolicy : uint8
{
	Reset,
	Keep,
};
