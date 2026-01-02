// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
	
#pragma once
#include "VectorDamper.h"

#include "SpringDampingSettings.generated.h"

USTRUCT(BlueprintType)
struct MEDIAPIPEMOTION_API FSpringDampingSettings
{
	FSpringDampingSettings() {}
	
	FSpringDampingSettings(const FSpringDampingSettings& Other)
		: bSpringDamperEnabled(Other.bSpringDamperEnabled),
		  SpringDamper(Other.SpringDamper)
	{
	}

	FSpringDampingSettings(FSpringDampingSettings&& Other) noexcept
		: bSpringDamperEnabled(Other.bSpringDamperEnabled),
		  SpringDamper(std::move(Other.SpringDamper))
	{
	}

	FSpringDampingSettings& operator=(const FSpringDampingSettings& Other)
	{
		if (this == &Other)
			return *this;
		bSpringDamperEnabled = Other.bSpringDamperEnabled;
		SpringDamper = Other.SpringDamper;
		return *this;
	}

	FSpringDampingSettings& operator=(FSpringDampingSettings&& Other) noexcept
	{
		if (this == &Other)
			return *this;
		bSpringDamperEnabled = Other.bSpringDamperEnabled;
		SpringDamper = std::move(Other.SpringDamper);
		return *this;
	}

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	bool bSpringDamperEnabled = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe", meta = (EditCondition = "bSpringDamperEnabled"))
	FVectorDamper SpringDamper;

	bool IsEnabled() const
	{
		return bSpringDamperEnabled && SpringDamper.Stiffness > (1.e-4f);
	}
};
