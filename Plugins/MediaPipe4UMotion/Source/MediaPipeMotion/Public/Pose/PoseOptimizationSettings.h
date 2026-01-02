// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "PoseOptimizationSettings.generated.h"

USTRUCT(BlueprintType)
struct MEDIAPIPEMOTION_API FPoseOptimizationSettings 
{
	FPoseOptimizationSettings(){}

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Optimization")
	bool bOptimizeShoulder = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Optimization")
	bool bOptimizeChest = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Optimization")
	bool bOptimizeLowerLeg = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Optimization")
	bool bOptimizeFoot = true;
};
