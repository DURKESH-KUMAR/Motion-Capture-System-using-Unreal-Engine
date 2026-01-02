// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once

#include "CoreMinimal.h"
#include "HumanoidBones.h"
#include "MediaPipeBone.h"
#include "Animation/Skeleton.h"
#include "UObject/Object.h"
#include "MediaPipeRemapAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, NotBlueprintable, hideCategories=Object)
class MEDIAPIPEMOTION_API UMediaPipeRemapAsset : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Skeleton")
	 USkeletalMesh* SkeletalMesh;

	UPROPERTY(EditAnywhere, Category="Body")
	FMediaPipeBone Root;

	UPROPERTY(EditAnywhere, Category="Body")
	FMediaPipeBone Hips;

	UPROPERTY(EditAnywhere, Category="Body")
	FMediaPipeBone LeftUpperLeg;

	UPROPERTY(EditAnywhere, Category="Body")
	FMediaPipeBone RightUpperLeg;

	UPROPERTY(EditAnywhere, Category="Body")
	FMediaPipeBone LeftLowerLeg;

	UPROPERTY(EditAnywhere, Category="Body")
	FMediaPipeBone RightLowerLeg;

	UPROPERTY(EditAnywhere, Category="Body")
	FMediaPipeBone LeftFoot;

	UPROPERTY(EditAnywhere, Category="Body")
	FMediaPipeBone RightFoot;

	UPROPERTY(EditAnywhere, Category="Body")
	FMediaPipeBone LeftToe;

	UPROPERTY(EditAnywhere, Category="Body")
	FMediaPipeBone RightToe;

	UPROPERTY(EditAnywhere, Category="Body")
	FMediaPipeBone Spine;

	UPROPERTY(EditAnywhere, Category="Body")
	FMediaPipeBone Chest;

	UPROPERTY(EditAnywhere, Category="Body")
	FMediaPipeBone Neck;

	UPROPERTY(EditAnywhere, Category="Body")
	FMediaPipeBone Head;

	UPROPERTY(EditAnywhere, Category="Body")
	FMediaPipeBone LeftShoulder;

	UPROPERTY(EditAnywhere, Category="Body")
	FMediaPipeBone RightShoulder;

	UPROPERTY(EditAnywhere, Category="Body")
	FMediaPipeBone LeftUpperArm;

	UPROPERTY(EditAnywhere, Category="Body")
	FMediaPipeBone RightUpperArm;

	UPROPERTY(EditAnywhere, Category="Body")
	FMediaPipeBone LeftLowerArm;

	UPROPERTY(EditAnywhere, Category="Body")
	FMediaPipeBone RightLowerArm;

	UPROPERTY(EditAnywhere, Category="Body")
	FMediaPipeBone LeftHand;

	UPROPERTY(EditAnywhere, Category="Body")
	FMediaPipeBone RightHand;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone LeftThumbProximal;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone LeftThumbIntermediate;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone LeftThumbDistal;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone LeftIndexProximal;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone LeftIndexIntermediate;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone LeftIndexDistal;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone LeftMiddleProximal;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone LeftMiddleIntermediate;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone LeftMiddleDistal;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone LeftRingProximal;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone LeftRingIntermediate;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone LeftRingDistal;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone LeftLittleProximal;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone LeftLittleIntermediate;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone LeftLittleDistal;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone RightThumbProximal;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone RightThumbIntermediate;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone RightThumbDistal;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone RightIndexProximal;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone RightIndexIntermediate;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone RightIndexDistal;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone RightMiddleProximal;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone RightMiddleIntermediate;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone RightMiddleDistal;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone RightRingProximal;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone RightRingIntermediate;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone RightRingDistal;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone RightLittleProximal;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone RightLittleIntermediate;

	UPROPERTY(EditAnywhere, Category="Fingers")
	FMediaPipeBone RightLittleDistal;


	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	void GetBoneMapping(TMap<EHumanoidBones, FName>& OutMappings) const;

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	FName GetBone(EHumanoidBones Bone) const;
};
