// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "CoreMinimal.h"
#include "TwistCorrectionSettings.generated.h"

USTRUCT(BlueprintType)
struct MEDIAPIPEMOTION_API FTwistCorrectionSettings
{
	FTwistCorrectionSettings(const FTwistCorrectionSettings& Other)
		: WristCorrectAlpha(Other.WristCorrectAlpha),
		  LowerArmCorrectAlpha(Other.LowerArmCorrectAlpha),
		  HeadCorrectAlpha(Other.HeadCorrectAlpha)
	{
	}

	FTwistCorrectionSettings(FTwistCorrectionSettings&& Other) noexcept
		: WristCorrectAlpha(Other.WristCorrectAlpha),
		  LowerArmCorrectAlpha(Other.LowerArmCorrectAlpha),
		  HeadCorrectAlpha(Other.HeadCorrectAlpha)
	{
	}

	FTwistCorrectionSettings& operator=(const FTwistCorrectionSettings& Other)
	{
		if (this == &Other)
			return *this;
		WristCorrectAlpha = Other.WristCorrectAlpha;
		LowerArmCorrectAlpha = Other.LowerArmCorrectAlpha;
		HeadCorrectAlpha = Other.HeadCorrectAlpha;
		return *this;
	}

	FTwistCorrectionSettings& operator=(FTwistCorrectionSettings&& Other) noexcept
	{
		if (this == &Other)
			return *this;
		WristCorrectAlpha = Other.WristCorrectAlpha;
		LowerArmCorrectAlpha = Other.LowerArmCorrectAlpha;
		HeadCorrectAlpha = Other.HeadCorrectAlpha;
		return *this;
	}

	GENERATED_BODY()
	FTwistCorrectionSettings(){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	float WristCorrectAlpha = 0.8f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	float LowerArmCorrectAlpha = 0.15f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	float HeadCorrectAlpha = 0.5f;
};
