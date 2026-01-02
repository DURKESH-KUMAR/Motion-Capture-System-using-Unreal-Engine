// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once
#include "RunTimeTypes.generated.h"

UENUM()
enum class EHandType : uint8
{
	Left,
	Right,
};

UENUM()
enum class EFootType: uint8
{
	Left,
	Right,
};


UENUM()
enum class EEyeType: uint8
{
	Left,
	Right,
};

UENUM()
enum class EFingerType: uint8
{
	Thumb,
	Index,
	Middle,
	Ring,
	Pinky
};