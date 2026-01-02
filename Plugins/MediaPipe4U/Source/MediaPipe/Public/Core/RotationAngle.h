// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once
#include "RotationAngle.generated.h"


UENUM(BlueprintType)
enum class ERotationAngle : uint8
{
	Rotation0,
	Rotation90,
	Rotation180,
	Rotation270,
};

namespace RotationAngleUtils
{
	inline int RotationAngleValue(const ERotationAngle RotationAngle)
	{
		switch (RotationAngle)
		{
		case ERotationAngle::Rotation0:
			return 0;
		case ERotationAngle::Rotation90:
			return 90;
		case ERotationAngle::Rotation180:
			return 180;
		case ERotationAngle::Rotation270:
			return 270;
		default:
			return 0;
		}
	}

	inline bool GetRotationAngle(int AngleDegrees, ERotationAngle& OutAngle)
	{
		if(AngleDegrees == 0)
		{
			OutAngle = ERotationAngle::Rotation0;
			return true;
		}
		if(AngleDegrees == 90)
		{
			OutAngle = ERotationAngle::Rotation90;
			return true;
		}
		if(AngleDegrees == 180)
		{
			OutAngle = ERotationAngle::Rotation180;
			return true;
		}
		if(AngleDegrees == 270)
		{
			OutAngle = ERotationAngle::Rotation270;
			return true;
		}
		return false;
	}

	inline ERotationAngle AddRotationAngle(const ERotationAngle A, const ERotationAngle B)
	{
		auto value = RotationAngleValue(A) + RotationAngleValue(B);
		value = value % 360;
		ERotationAngle a = ERotationAngle::Rotation0;
		GetRotationAngle(value, a);
		return a;
	}
}
