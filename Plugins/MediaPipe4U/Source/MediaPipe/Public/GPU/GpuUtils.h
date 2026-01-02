// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CudaCheckResult.h"


class MEDIAPIPE_API FGpuUtils
{
public:
	static void CheckCuda(FCudaCheckResult& OutResult);

	static bool SetCudaDevice(int DeviceIndex);

	static FString GetCudaDllFolder();

	static FString GetCudnnDllFolder();
};
