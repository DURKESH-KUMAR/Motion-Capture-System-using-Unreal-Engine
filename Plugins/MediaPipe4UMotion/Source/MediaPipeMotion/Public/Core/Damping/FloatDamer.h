// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FloatDamer.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct MEDIAPIPEMOTION_API FFloatDamer
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damping")
	float Stiffness = 450.0f;
};
