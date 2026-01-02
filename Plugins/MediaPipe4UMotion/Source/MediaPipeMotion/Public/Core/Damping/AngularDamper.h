// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonePose.h"
#include "Kismet/KismetMathLibrary.h"
#include "AngularDamper.generated.h"

USTRUCT(BlueprintType)
struct MEDIAPIPEMOTION_API FAngularDamper
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Swing", meta=(ClampMin = 0, ClampMax = 180))
	float PitchSwing = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Swing", meta=(ClampMin = 0, ClampMax = 180))
	float YawSwing = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Swing", meta=(ClampMin = 0, ClampMax = 180))
	float RollSwing = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damping")
	float Stiffness = 250.0f;
};