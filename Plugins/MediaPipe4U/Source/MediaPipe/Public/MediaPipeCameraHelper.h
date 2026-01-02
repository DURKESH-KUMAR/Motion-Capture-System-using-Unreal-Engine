// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "MediaPipeLandmark.h"
#include "Containers/Array.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MediaPipeCameraHelper.generated.h"

USTRUCT(BlueprintType)
struct MEDIAPIPE_API FCameraParameters
{
	GENERATED_BODY()
	
	float FocalLength = 0.0f;
	float HorizontalFOV = 0.0f;
	float FocalLengthY = 0.0f;
	float VerticalFOV = 0.0f;
	FCameraParameters() {}

	FCameraParameters(const FCameraParameters& Other)
		: FocalLength(Other.FocalLength),
		  HorizontalFOV(Other.HorizontalFOV),
		  FocalLengthY(Other.FocalLengthY),
		  VerticalFOV(Other.VerticalFOV)
	{
	}

	FCameraParameters(FCameraParameters&& Other) noexcept
		: FocalLength(Other.FocalLength),
		  HorizontalFOV(Other.HorizontalFOV),
		  FocalLengthY(Other.FocalLengthY),
		  VerticalFOV(Other.VerticalFOV)
	{
	}

	FCameraParameters& operator=(const FCameraParameters& Other)
	{
		if (this == &Other)
			return *this;
		FocalLength = Other.FocalLength;
		HorizontalFOV = Other.HorizontalFOV;
		FocalLengthY = Other.FocalLengthY;
		VerticalFOV = Other.VerticalFOV;
		return *this;
	}

	FCameraParameters& operator=(FCameraParameters&& Other) noexcept
	{
		if (this == &Other)
			return *this;
		FocalLength = Other.FocalLength;
		HorizontalFOV = Other.HorizontalFOV;
		FocalLengthY = Other.FocalLengthY;
		VerticalFOV = Other.VerticalFOV;
		return *this;
	}
};

UCLASS(meta=(BlueprintThreadSafe, ScriptName = "MediaPipeCameraHelper"))
class MEDIAPIPE_API UMediaPipeCameraHelper :  public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintPure, Category="MediaPipe Camera Helper", meta=(ReturnDisplayName="Pixel Focal Length"))
	static float CalculatePixelFocalLength(float FocalLengthMM, float SensorWidthMM, int ImageWidthPixels);
	
	UFUNCTION(BlueprintPure, Category="MediaPipe Camera Helper", meta=(ReturnDisplayName="Pixel Focal Length"))
	static float CalculateFocalLength(int ImageWidth, float HorizontalFOV);

	UFUNCTION(BlueprintPure, Category="MediaPipe Camera Helper", meta=(ReturnDisplayName="Camera Parameters"))
	static FCameraParameters EstimateCamperParameters(const TArray<FMediaPipeLandmark>& PoseLandmarks2D,  int ImageWidth, int ImageHeight, float RealDepthInCM = 200.0f);
	
	UFUNCTION(BlueprintPure, Category="MediaPipe Camera Helper", meta=(ReturnDisplayName="Depth"))
	static float EstimateDepth(const TArray<FMediaPipeLandmark>& PoseLandmarks2D,  int ImageWidth, int ImageHeight, float FocalLengthInPixel = 800.0f);
	/**
	 * The average shoulder width for an adult can be set to 0.4 meters (40 centimeters), which is a common assumption in most computer vision and virtual scenarios.
	 */
	static constexpr float REAL_SHOULDER_WIDTH = 40; // in cm
private:
	
	static bool CalculateVerticalFovAndLength(int ImageWidth, int ImageHeight, float HorizontalFOV, FCameraParameters& InOut);
	static FVector2D ConvertNormalizedToScreen(float NormalizedX, float NormalizedY, int ImageWidth, int ImageHeight);
	static float EstimateDepth(float ShoulderWidth, float RealShoulderWidth, float FocalLength);
	static float EstimateFocalLength(float ShoulderWidth, float RealWidth, float Depth);
	static bool GetShoulderWidthInPixel(const TArray<FMediaPipeLandmark>& PoseLandmarks2D, int ImageWidth, int ImageHeight, float& PixelDistance);
};
