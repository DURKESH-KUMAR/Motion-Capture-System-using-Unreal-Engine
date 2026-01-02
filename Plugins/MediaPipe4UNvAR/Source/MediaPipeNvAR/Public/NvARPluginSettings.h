// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NvARPluginSettings.generated.h"

/**
 * 
 */
UCLASS(config = MediaPipeNvAR, DefaultConfig)
class MEDIAPIPENVAR_API UNvARPluginSettings : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(config, EditAnywhere, Category = "NvAR")
	int UseGPU = 0;
	
	UPROPERTY(config, EditAnywhere, Category = "NvAR")
	bool bFaceExpressionEnabled = true;

	UPROPERTY(config, EditAnywhere, Category = "NvAR")
	bool bPoseTrackingEnabled = false;
};
