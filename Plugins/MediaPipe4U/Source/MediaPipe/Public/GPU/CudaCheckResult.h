// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once

struct MEDIAPIPE_API FCudaCheckResult
{
	bool bSupported = false;
	int MajorVerMax = 0;
	int MinorVerMax = 0;

	FCudaCheckResult() {}
	
	FCudaCheckResult(const FCudaCheckResult& Other)
		: bSupported(Other.bSupported),
		  MajorVerMax(Other.MajorVerMax),
		  MinorVerMax(Other.MinorVerMax)
	{
	}

	FCudaCheckResult(FCudaCheckResult&& Other) noexcept
		: bSupported(Other.bSupported),
		  MajorVerMax(Other.MajorVerMax),
		  MinorVerMax(Other.MinorVerMax)
	{
	}

	FCudaCheckResult& operator=(const FCudaCheckResult& Other)
	{
		if (this == &Other)
			return *this;
		bSupported = Other.bSupported;
		MajorVerMax = Other.MajorVerMax;
		MinorVerMax = Other.MinorVerMax;
		return *this;
	}

	FCudaCheckResult& operator=(FCudaCheckResult&& Other) noexcept
	{
		if (this == &Other)
			return *this;
		bSupported = Other.bSupported;
		MajorVerMax = Other.MajorVerMax;
		MinorVerMax = Other.MinorVerMax;
		return *this;
	}
};