// Copyright (c) 2025 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once

#include "CoreMinimal.h"
#include "ARKitBlendShape.h"
#include "UObject/Object.h"
#include "ARKitCurveRemapAsset.generated.h"

/**
 * Map your curve name to standard ARKit curve name.
 */
UCLASS(BlueprintType, NotBlueprintable, hideCategories=Object)
class MEDIAPIPE_API UARKitCurveRemapAsset : public UObject
{
	GENERATED_BODY()

	UARKitCurveRemapAsset();
public:
		// Left eye blend shapes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Eyes") FName EyeBlinkLeft = FName(TEXT("EyeBlinkLeft"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Eyes") FName EyeLookDownLeft = FName(TEXT("EyeLookDownLeft"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Eyes") FName EyeLookInLeft = FName(TEXT("EyeLookInLeft"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Eyes") FName EyeLookOutLeft = FName(TEXT("EyeLookOutLeft"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Eyes") FName EyeLookUpLeft = FName(TEXT("EyeLookUpLeft"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Eyes") FName EyeSquintLeft = FName(TEXT("EyeSquintLeft"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Eyes") FName EyeWideLeft = FName(TEXT("EyeWideLeft"));

	// Right eye blend shapes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Eyes") FName EyeBlinkRight = FName(TEXT("EyeBlinkRight"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Eyes") FName EyeLookDownRight = FName(TEXT("EyeLookDownRight"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Eyes") FName EyeLookInRight = FName(TEXT("EyeLookInRight"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Eyes") FName EyeLookOutRight = FName(TEXT("EyeLookOutRight"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Eyes") FName EyeLookUpRight = FName(TEXT("EyeLookUpRight"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Eyes") FName EyeSquintRight = FName(TEXT("EyeSquintRight"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Eyes") FName EyeWideRight = FName(TEXT("EyeWideRight"));

	// Jaw blend shapes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Jaw") FName JawForward = FName(TEXT("JawForward"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Jaw") FName JawLeft = FName(TEXT("JawLeft"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Jaw") FName JawRight = FName(TEXT("JawRight"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Jaw") FName JawOpen = FName(TEXT("JawOpen"));

	// Mouth blend shapes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Mouth") FName MouthClose = FName(TEXT("MouthClose"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Mouth") FName MouthFunnel = FName(TEXT("MouthFunnel"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Mouth") FName MouthPucker = FName(TEXT("MouthPucker"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Mouth") FName MouthLeft = FName(TEXT("MouthLeft"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Mouth") FName MouthRight = FName(TEXT("MouthRight"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Mouth") FName MouthSmileLeft = FName(TEXT("MouthSmileLeft"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Mouth") FName MouthSmileRight = FName(TEXT("MouthSmileRight"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Mouth") FName MouthFrownLeft = FName(TEXT("MouthFrownLeft"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Mouth") FName MouthFrownRight = FName(TEXT("MouthFrownRight"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Mouth") FName MouthDimpleLeft = FName(TEXT("MouthDimpleLeft"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Mouth") FName MouthDimpleRight = FName(TEXT("MouthDimpleRight"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Mouth") FName MouthStretchLeft = FName(TEXT("MouthStretchLeft"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Mouth") FName MouthStretchRight = FName(TEXT("MouthStretchRight"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Mouth") FName MouthRollLower = FName(TEXT("MouthRollLower"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Mouth") FName MouthRollUpper = FName(TEXT("MouthRollUpper"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Mouth") FName MouthShrugLower = FName(TEXT("MouthShrugLower"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Mouth") FName MouthShrugUpper = FName(TEXT("MouthShrugUpper"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Mouth") FName MouthPressLeft = FName(TEXT("MouthPressLeft"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Mouth") FName MouthPressRight = FName(TEXT("MouthPressRight"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Mouth") FName MouthLowerDownLeft = FName(TEXT("MouthLowerDownLeft"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Mouth") FName MouthLowerDownRight = FName(TEXT("MouthLowerDownRight"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Mouth") FName MouthUpperUpLeft = FName(TEXT("MouthUpperUpLeft"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Mouth") FName MouthUpperUpRight = FName(TEXT("MouthUpperUpRight"));

	// Brow blend shapes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Brows") FName BrowDownLeft = FName(TEXT("BrowDownLeft"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Brows") FName BrowDownRight = FName(TEXT("BrowDownRight"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Brows") FName BrowInnerUp = FName(TEXT("BrowInnerUp"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Brows") FName BrowOuterUpLeft = FName(TEXT("BrowOuterUpLeft"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Brows") FName BrowOuterUpRight = FName(TEXT("BrowOuterUpRight"));

	// Cheek blend shapes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Cheeks") FName CheekPuff = FName(TEXT("CheekPuff"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Cheeks") FName CheekSquintLeft = FName(TEXT("CheekSquintLeft"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Cheeks") FName CheekSquintRight = FName(TEXT("CheekSquintRight"));

	// Nose blend shapes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Nose") FName NoseSneerLeft = FName(TEXT("NoseSneerLeft"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Nose") FName NoseSneerRight = FName(TEXT("NoseSneerRight"));

	// Tongue
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Tongue") FName TongueOut = FName(TEXT("TongueOut"));

	// Head rotation (as curves)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Head") FName HeadYaw = FName(TEXT("HeadYaw"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Head") FName HeadPitch = FName(TEXT("HeadPitch"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Head") FName HeadRoll = FName(TEXT("HeadRoll"));

	// Eye rotation (as curves)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Eyes") FName LeftEyeYaw = FName(TEXT("LeftEyeYaw"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Eyes") FName LeftEyePitch = FName(TEXT("LeftEyePitch"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Eyes") FName LeftEyeRoll = FName(TEXT("LeftEyeRoll"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Eyes") FName RightEyeYaw = FName(TEXT("RightEyeYaw"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Eyes") FName RightEyePitch = FName(TEXT("RightEyePitch"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Curves/Eyes") FName RightEyeRoll = FName(TEXT("RightEyeRoll"));


	const FName& GetCurveName(EARKitBlendShape BlendShape) const;
	const FName& GetCurveName(const FName& BlendShapeName) const;
private:
	TMap<const FName, const FName*> BlendShapeNameMap;
};
