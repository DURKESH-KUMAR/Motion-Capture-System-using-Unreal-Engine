// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once

#include "VectorDamper.generated.h"

USTRUCT(BlueprintType)
struct MEDIAPIPEMOTION_API FVectorDamper
{
	GENERATED_BODY()

	FVectorDamper(){}
	
	FVectorDamper(const FVectorDamper& Other)
		: Stiffness(Other.Stiffness),
		  SwingX(Other.SwingX),
		  SwingY(Other.SwingY),
		  SwingZ(Other.SwingZ)
	{
	}

	FVectorDamper(FVectorDamper&& Other) noexcept
		: Stiffness(Other.Stiffness),
		  SwingX(Other.SwingX),
		  SwingY(Other.SwingY),
		  SwingZ(Other.SwingZ)
	{
	}

	FVectorDamper& operator=(const FVectorDamper& Other)
	{
		if (this == &Other)
			return *this;
		Stiffness = Other.Stiffness;
		SwingX = Other.SwingX;
		SwingY = Other.SwingY;
		SwingZ = Other.SwingZ;
		return *this;
	}

	FVectorDamper& operator=(FVectorDamper&& Other) noexcept
	{
		if (this == &Other)
			return *this;
		Stiffness = Other.Stiffness;
		SwingX = Other.SwingX;
		SwingY = Other.SwingY;
		SwingZ = Other.SwingZ;
		return *this;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damping", meta = (ClampMin=0.f, ClampMax=2000.f))
	float Stiffness = 450.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damping", meta=(ClampMin= 0, ClampMax=100))
	float SwingX = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damping", meta=(ClampMin= 0, ClampMax=100))
	float SwingY = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damping", meta=(ClampMin= 0, ClampMax=100))
	float SwingZ = 0;
};
