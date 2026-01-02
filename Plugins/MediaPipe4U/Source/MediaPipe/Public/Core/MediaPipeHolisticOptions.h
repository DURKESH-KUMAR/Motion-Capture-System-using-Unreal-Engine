// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once
#include "RotationAngle.h"
#include "MediaPipeHolisticOptions.generated.h"

UENUM(BlueprintType)
enum class EMediaPipeToggle : uint8
{ 
	Disabled,
	Enabled,
	Auto,
};

USTRUCT(BlueprintType)
struct MEDIAPIPE_API FMediaPipeHolisticOptions
{

	GENERATED_BODY()

	FMediaPipeHolisticOptions(){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe | Holistic")
	ERotationAngle InputAngle = ERotationAngle::Rotation0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe | Holistic")
	bool InputHorizontallyFlipped = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe | Holistic")
	bool bInputVerticallyFlipped = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe | Holistic")
	bool bSmoothLandmarks = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe | Holistic")
	EMediaPipeToggle FaceLandmarksEnabled = EMediaPipeToggle::Auto;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe | Holistic")
	EMediaPipeToggle FaceBlendShapesEnabled = EMediaPipeToggle::Auto;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe | Holistic")
	EMediaPipeToggle HandLandmarksEnabled = EMediaPipeToggle::Auto;

	/**
	 * For custom mediapipe connector, we can pass custom parameters through this property.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe | Holistic", meta=(ToolTip="Use for custom mediapipe connector to pass parameters."))
	TMap<FString, FString> CustomParameters;
};
