// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once
#include <functional>

#include "HeadCorrectionEnvironment.h"
#include "HumanoidBoneSettings.h"
#include "HumanoidKeyJoint.h"
#include "AngularDamper.h"
#include "LiveLinkTypes.h"
#include "LocationSolvingStaging.h"
#include "MediaPipeAnimExtensions.h"
#include "MediaPipeAnimMode.h"
#include "MediaPipeSource.h"
#include "PoseAssetContainer.h"
#include "TwistCorrectionSettings.h"
#include "WristCorrectionEnvironment.h"


class UMediaPipeAnimInstance;
struct FMediaPipeAnimInstanceProxy;
struct FAnimNode_MediaPipePose;

class MEDIAPIPEMOTION_API FMediaPipeAnimContext
{
public:
	typedef std::function<void(IMediaPipeAnimExtensions* Extension)> ExtensionAction;
	FMediaPipeAnimContext(TWeakPtr<FHumanoidBoneSettings> BoneConfig): BoneSettings(BoneConfig)
	{
		
	}

	bool IsBoneSettingsLoaded() const;
	
	TArray<TWeakObjectPtr<UObject>> Extensions;
	TWeakPtr<FHumanoidBoneSettings> BoneSettings;
	TSharedPtr<FMediaPipeSource> MediaPipeSource;
	TSet<EHumanoidBodyPart> SharedDampers;
	TSharedPtr<FLocationSolvingStaging> LocationStaging;

	TOptional<FRotator> BodyRotator;
	float DeltaSeconds = 0;
	EMediaPipeAnimMode Mode = EMediaPipeAnimMode::FullBody;

	float HandScoreThresh = 0.5f;
	
	bool bIsTwistCorrectionEnabled = false;
	bool bIsStaticImageSource = false;
	int ImageWidth = 0;
	int ImageHeight = 0;

	bool bHeadSolverRegister = false;
	bool bHandSolverRegister = false;
	bool bPoseSolverRegister = false;
	bool bLocationSolverRegister = false;
	bool bGroundSolverRegister = false;

	bool bLeftHandVisible = true;
	bool bRightHandVisible = true;

	int PoseHandled = 0;
	int PoseHandlerCount = 0;

	bool bIsAnimationPaused = false;
	FVector MovementVelocity = FVector::ZeroVector;

#pragma region TwistCorrection

	FWristCorrectionEnvironment LeftWristCorrectionEnvironment;
	FWristCorrectionEnvironment RightWristCorrectionEnvironment;
	FHeadCorrectionEnvironment HeadCorrectionEnvironment;

#pragma endregion 

	const FTransform& GetComponentTransform();
	void ForeachExtensions(ExtensionAction Action, bool bIncludeDisabled = false);
	void ForeachExtensionsReverse(ExtensionAction Action, bool bIncludeDisabled = false);
	FTwistCorrectionSettings& GetTwistCorrectionSettings();
	bool IsDebugDrawEnabled() const;
	bool NeedIgnorePose();
	bool IsSolveHead() const;
	bool IsSolveFingers() const;
	bool IsLiveLinkEnabled() const;
	bool IsMediaPipeRunning() const;
	FLiveLinkSubjectName GetLiveLinkSubject() const;
	UWorld* GetWorld() const;
	void ResetState();

	bool IsUpperBodyMode() const;
	bool IsFullBodyMode() const;
	bool HasSource() const;

	FMediaPipeFrame& GetPoseWorldFrame();
	FMediaPipeFrame& GetPoseFrame();
	FMediaPipeFrame& GetLeftHandFrame();
	FMediaPipeFrame& GetRightHandFrame();
	FMediaPipeFrame& GetFaceFrame();

	void RefreshFrames();
	
	FPoseAssetContainer* GetPoseAsset() const;
	bool HasInitPoseAsset() const;
	FName GetInitPoseName() const;
	
private:
	bool bIsBoneSettingsLoaded = false;
	FTwistCorrectionSettings TwistCorrectionSettings{};

	FMediaPipeFrame PoseWorldFrame{};
	FMediaPipeFrame PoseFrame{};
	FMediaPipeFrame LeftHandFrame{};
	FMediaPipeFrame RightHandFrame{};
	FMediaPipeFrame FaceFrame{};

	bool bPoseWorldFrameUpdated = false;
	bool PoseFrameUpdated = false;
	bool LeftHandFrameUpdated = false;
	bool RightHandFrameUpdated = false;
	bool FaceFrameUpdated = false;
	
protected:
	FTransform ComponentTransform;
	bool bEnableLivelink = true;
	bool bIsMediaPipeRunning = false;
	bool bSolveHead = false;  
	bool bSolveFingers = false;
	bool bDebugDraw = false;
	UWorld* World = nullptr;
	FLiveLinkSubjectName LiveLinkSubject;
	TSharedPtr<FPoseAssetContainer> PoseAsset;
	FName InitPoseName;
	
	friend class UMediaPipeAnimInstance;
	friend struct FMediaPipeAnimInstanceProxy;
	friend struct FAnimNode_MediaPipePose;
};
