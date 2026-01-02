// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once
#include <functional>
#include <string>

#include "CoreMinimal.h"
#include "BoneItem.h"
#include "MediaPipeAnimInstance.h"
#include "MediaPipeAnimMode.h"
#include "MediaPipePluginInfo.h"
#include "TwistCorrectionResult.h"
#include "Components/Image.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Animation/AnimTypes.h"
#include "MediaPipeLandmark.h"
#include "GroundSolveSettings.h"
#include "Kismet/GameplayStatics.h"
#include "PoseOptimizationSettings.h"
#include "RotationLockConfig.h"
#include "Async/Async.h"
#include "MediaPipeUtils.h"

#include "MediaPipeMotionUtils.generated.h"

struct FMediaPipeAnimInstanceProxy;



UCLASS(meta=(BlueprintThreadSafe, ScriptName = "MediaPipeMotionUtils"))
class MEDIAPIPEMOTION_API UMediaPipeMotionUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	
	UFUNCTION(BlueprintCallable, Category="MediaPipe", meta=(ReturnDisplayName="Found"))
	static bool FindSkeletalMeshComponent(AActor* Actor,
															 USkeletalMeshComponent*& OutSkeletalMeshComponent);

	UFUNCTION(BlueprintCallable, Category="MediaPipe", meta=(ReturnDisplayName="Found"))
	static bool FindMediaPipeAnimationInstance(AActor* Actor,
	                                                         UMediaPipeAnimInstance*& MediaPipeAnimInstance);

	UFUNCTION(BlueprintCallable, Category="MediaPipe", meta=(ReturnDisplayName="MediaPipe Animation Instance"))
	static UMediaPipeAnimInstance* FindFirstMediaPipeAnimInstance(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="MediaPipe", meta=(ReturnDisplayName="Optimized"))
	static bool GetPoseOptimize(UMediaPipeAnimInstance* MediaPipeAnimInstance);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static void SetPoseOptimize(UMediaPipeAnimInstance* MediaPipeAnimInstance, bool bOptimize);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static bool SetPoseOptimizationSettings(UMediaPipeAnimInstance* MediaPipeAnimInstance, const FPoseOptimizationSettings& Settings);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static bool GetPoseOptimizationSettings(UMediaPipeAnimInstance* MediaPipeAnimInstance, FPoseOptimizationSettings& Settings);

	UFUNCTION(BlueprintPure, Category="MediaPipe", meta=(ReturnDisplayName="Optimized"))
	static bool GetHandOptimize(UMediaPipeAnimInstance* MediaPipeAnimInstance);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static void SetHandOptimize(UMediaPipeAnimInstance* MediaPipeAnimInstance, bool bOptimize);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static void SetPoseSmooth(UMediaPipeAnimInstance* MediaPipeAnimInstance, float Smooth);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static void SetArmIKEnabled(UMediaPipeAnimInstance* MediaPipeAnimInstance, bool bEnabled);

	UFUNCTION(BlueprintPure, Category="MediaPipe", meta=(ReturnDisplayName="Enabled"))
	static bool IsArmIKEnabled(UMediaPipeAnimInstance* MediaPipeAnimInstance);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static void SetLegIKEnabled(UMediaPipeAnimInstance* MediaPipeAnimInstance, bool bEnabled);

	UFUNCTION(BlueprintPure, Category="MediaPipe", meta=(ReturnDisplayName="Enabled"))
	static bool IsLegIKEnabled(UMediaPipeAnimInstance* MediaPipeAnimInstance);

	UFUNCTION(BlueprintPure, Category="MediaPipe", meta=(ReturnDisplayName="Enabled"))
	static bool IsGroundIKEnabled(UMediaPipeAnimInstance* MediaPipeAnimInstance);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static bool SetCountdownCalibrationEnabled(UMediaPipeAnimInstance* MediaPipeAnimInstance, bool bPoseCalibrationEnabled = true, bool bLocationEnabled = true);

	UFUNCTION(BlueprintPure, Category="MediaPipe", meta=(ReturnDisplayName="Enabled"))
	static void GetCountdownCalibrationEnabled(UMediaPipeAnimInstance* MediaPipeAnimInstance, bool& bPoseCalibrationEnabled, bool& bLocationEnabled);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static bool SetPoseCalibrationFlags(UMediaPipeAnimInstance* MediaPipeAnimInstance, UPARAM(meta=(Bitmask, BitmaskEnum =" /Script/MediaPipe.EPoseCalibrationFlags")) uint8 Flags);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static void SetGroundIKEnabled(UMediaPipeAnimInstance* MediaPipeAnimInstance, bool bEnabled);

	UFUNCTION(BlueprintCallable, Category="MediaPipe", meta=(ReturnDisplayName="Success"))
	static bool SetGroundIKSettings(UMediaPipeAnimInstance* MediaPipeAnimInstance, const FGroundSolveSettings& InSettings);

	UFUNCTION(BlueprintCallable, Category="MediaPipe", meta=(ReturnDisplayName="Success"))
	static bool GetGroundIKSettings(UMediaPipeAnimInstance* MediaPipeAnimInstance, FGroundSolveSettings& OutSettings);

	UFUNCTION(BlueprintCallable, Category="MediaPipe", meta=(ReturnDisplayName="Success"))
	static bool GetPoseSmooth(UMediaPipeAnimInstance* MediaPipeAnimInstance, float& Smooth);

	UFUNCTION(BlueprintCallable, Category="MediaPipe", meta=(ReturnDisplayName="Success"))
	static bool SetFingerSmooth(UMediaPipeAnimInstance* MediaPipeAnimInstance, float Smooth);

	UFUNCTION(BlueprintCallable, Category="MediaPipe", meta=(ReturnDisplayName="Success"))
	static bool GetFingerSmooth(UMediaPipeAnimInstance* MediaPipeAnimInstance, float& Smooth);

	UFUNCTION(BlueprintCallable, Category="MediaPipe", meta=(ReturnDisplayName="Success"))
	static bool SetJointLocks(UMediaPipeAnimInstance* MediaPipeAnimInstance,
	                                        const FPoseSolverLockSettings& InLocks);

	UFUNCTION(BlueprintPure, Category="MediaPipe", meta=(ReturnDisplayName="Success"))
	static bool GetJointLocks(UMediaPipeAnimInstance* MediaPipeAnimInstance,
											FPoseSolverLockSettings& OutLocks);

	UFUNCTION(BlueprintPure, Category="MediaPipe")
	static void GetUpperBodyLocks(UMediaPipeAnimInstance* MediaPipeAnimInstance, bool& bLockPitch, bool& bLockYaw, bool& bLockRoll);
	
	UFUNCTION(BlueprintCallable, Category="MediaPipe", meta=(ReturnDisplayName="Success"))
	static bool SetUpperBodyLocks(UMediaPipeAnimInstance* MediaPipeAnimInstance, bool bLockPitch, bool bLockYaw, bool bLockRoll);
	
	UFUNCTION(BlueprintPure, Category="MediaPipe", meta=(ReturnDisplayName="Settings"))
	static FTwistCorrectionSettings GetTwistCorrectionSettings(UMediaPipeAnimInstance* MediaPipeAnimInstance); 
	
	UFUNCTION(BlueprintCallable, Category="MediaPipe", meta=(ReturnDisplayName="Success"))
	static bool SetTwistCorrectionSettings(UMediaPipeAnimInstance* MediaPipeAnimInstance,
											const FTwistCorrectionSettings& Settings); 

	UFUNCTION(BlueprintCallable, Category="MediaPipe", meta=(ReturnDisplayName="Found"))
	static bool FindMediaPipeAnimationMesh(AActor* Actor, USkeletalMeshComponent*& SkeletalMeshComponent);

	UFUNCTION(BlueprintCallable, Category="MediaPipe", meta=(ReturnDisplayName="Success"))
	static bool SetMediaPipeAnimationMode(AActor* Character, EMediaPipeAnimMode Mode);


	UFUNCTION(BlueprintCallable, Category="MediaPipe", meta=(ReturnDisplayName="Found"))
	static bool FindSkeletalMeshComponentByName(AActor* Actor, FName ComponentName,
	                                                          USkeletalMeshComponent*& OutSkeletalMeshComponent);
	

	UFUNCTION(BlueprintPure, Category="MediaPipe", meta=(ReturnDisplayName="MediaPipe Holistic Componen"))
	static UMediaPipeHolisticComponent* FindMediaPipeHolisticComponent(const UObject* WorldContextObject);

	// UFUNCTION(BlueprintCallable, Category="MediaPipe")
	// static UIKRigDefinition* CreateRigControl(const USkeletalMeshComponent* SkeletalMeshComponent, const FHumanoidBoneSettings& InSettings);
	//
	// UFUNCTION(BlueprintCallable, Category="MediaPipe")
	// static UIKRetargeter* CreateIKRetargeter(const FRuntimeRetargetSource& From, const FRuntimeRetargetSource& To);
	
	static FQuat RemoveTwist(const FTransform& InParentTransform, FTransform& InOutTransform,
	                         const FTransform& OriginalLocalTransform, const FVector& InAlignVector);
	
	static FTwistCorrectionResult CorrectTwist(
		FTransform& InOutParentLocalTransform,
		FTransform& InOutLocalTransform,
		const FTransform& OriginalLocalTransform,
		const FVector& InAlignVector,
		const FVector& InParentAlignVector,
		float Alpha,
		float InnerAngleDegree,
		float OuterAngleDegree);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static bool GetResolutionLimitSize(EResolutionLimits Limitation, int& LimitedWidth, int& LimitedHeight);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static FVector2D CalcImageSize(int TextureWidth, int TextureHeight, float MaxImageWidthPercent,
	                                             float MaxImageHeightPercent, int ScreenWidth, int ScreenHeight);

	UFUNCTION(BlueprintCallable, Category="MediaPipe", meta=(ReturnDisplayName="Success"))
	static bool LimitSizeByResolution(int TextureWidth, int TextureHeight, EResolutionLimits Limitation, FSizeInt& LimitedSize);
	
	UFUNCTION(BlueprintCallable, Category="MediaPipe", meta=(ReturnDisplayName="Success"))
	static bool LimitSize(int TextureWidth, int TextureHeight, int MaxWidth, int MaxHeight, FSizeInt& LimitedSize);

	UFUNCTION(BlueprintPure, Category="MediaPipe", meta=(ReturnDisplayName="Duration String"))
	static FString GetDurationString(int64 Millisecond);

	UFUNCTION(BlueprintPure, Category="MediaPipe", meta=(ReturnDisplayName="Plugin Info"))
	static FMediaPipePluginInfo PluginInfo();

	static TSharedPtr<IBoneSettingsProvider> CreatePresetBoneSettingsProvider(
		EBonePresets Preset, UMediaPipeRemapAsset* RemapAsset);

	static FCompactPoseBoneIndex GetPoseBoneIndex(const FCSPose<FCompactPose>& Pose, const FBoneReference& Bone);
 
	static FCompactPoseBoneIndex GetParentPoseBoneIndex(const FCSPose<FCompactPose>& Pose, const FBoneReference& Bone);

	// Get worldspace location of a bone
	static FVector GetBoneWorldLocation(USkeletalMeshComponent* SkelComp,
	                                                  FCSPose<FCompactPose>& MeshBases,
	                                                  FCompactPoseBoneIndex BoneIndex);

	// Get worldspace transform of a bone
	static FTransform GetBoneWorldTransform(USkeletalMeshComponent* SkelComp,
	                                                      FCSPose<FCompactPose>& MeshBases,
	                                                      FCompactPoseBoneIndex BoneIndex);

	// Get bonespace location of a bone
	static FVector GetBoneSpaceLocation(USkeletalMeshComponent* SkelComp,
	                                                  FCSPose<FCompactPose>& MeshBases,
	                                                  FCompactPoseBoneIndex BoneIndex);

	// Get bonespace transform of a bone
	static FTransform GetBoneSpaceTransform(USkeletalMeshComponent* SkelComp,
	                                                      FCSPose<FCompactPose>& MeshBases,
	                                                      FCompactPoseBoneIndex BoneIndex);
	
	static TOptional<FBoneTransform> GetBoneTransform(const FTransform& ComponentTransform, FCSPose<FCompactPose>& Pose,
	                                           FBoneReference& Bone, EBoneControlSpace BoneSpace);


	static TOptional<FBoneTransform> GetBoneTransform(const FTransform& ComponentTransform, FCSPose<FCompactPose>& Pose,
	                                                                FCompactPoseBoneIndex BoneIndex,
	                                                                EBoneControlSpace BoneSpace);

	static TOptional<FBoneTransform> GetBoneTransform(FComponentSpacePoseContext& Context,
																	const FBoneReference& Bone,
																	EBoneControlSpace BoneSpace);

	static TOptional<FBoneTransform> GetBoneTransform(FComponentSpacePoseContext& Context,
	                                                                FCompactPoseBoneIndex BoneIndex,
	                                                                EBoneControlSpace BoneSpace);

	static TOptional<FTransform> GetRefBoneTransform(const FReferenceSkeleton& RefSkeleton, const FName& BoneName, EBoneControlSpace BoneSpace = BCS_ComponentSpace);
	

	static TOptional<FBoneTransform> RotateBone(
		FComponentSpacePoseContext& Context,
		const FCompactPoseBoneIndex& BoneIndex,
		const FQuat& InRotation,
		EBoneControlSpace BoneSpace = BCS_ComponentSpace,
		EModificationMode Mode = EModificationMode::Replace,
		float Smooth = 0);

	
	
	
	static bool GetAllBonesInComponentSpace(const UAnimInstance* AnimInstance,
	                                                      TMap<FName, FBoneItem>& OutBones);

	static bool GetHeadTowardsFromFaceMesh(const TArray<FMediaPipeLandmark>& FaceMeshes, FVector& Forward, FVector& Up, std::function<FVector(int Index, const FVector&)> Filter);

	static bool GetHeadTowardsFromFaceMesh(const TArray<FMediaPipeLandmark>& FaceMeshes, FVector& Forward, FVector& Up);

	static FRotator CalculateBodyRotatorFromLandmarks(const TArray<FMediaPipeLandmark>& PoseLandmarks);
	static FRotator CalculateHeadRotatorFromFaceMesh(const TArray<FMediaPipeLandmark>& FaceMeshes);

	static void BuildBoneChainChildToParent(const FCSPose<FCompactPose>& Pose, const FBoneReference& RootBone, const FBoneReference& TipBone, TArray<FCompactPoseBoneIndex>& OutBoneChain);
	static void BuildBoneChainParentToChild(const FCSPose<FCompactPose>& Pose, const FBoneReference& RootBone, const FBoneReference& TipBone, TArray<FCompactPoseBoneIndex>& OutBoneChain);

	static bool GetBoneName(const FCompactPose& Pose, FCompactPoseBoneIndex CompactPoseBoneIndex, FName& BoneName);
	static bool GetBoneName(const FCompactPose& Pose, FMeshPoseBoneIndex MeshPoseBoneIndex, FName& BoneName);
	
	static const TArray<FMediaPipeLandmark> EmptyLandmarks;
	
	static FMediaPipeAnimInstanceProxy* GetMediaPipeAnimInstanceProxy(FAnimInstanceProxy* InProxy);
};



