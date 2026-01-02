// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once
#include "CoreMinimal.h"
#include "CalibrationMethod.h"
#include "HumanoidBoneSettings.h"
#include "MediaPipeAnimMode.h"
#include "MediaPipeFrame.h"
#include "SolverResetReason.h"
#include "Animation/AnimNodeBase.h"


class MEDIAPIPEMOTION_API IMediaPipeSolver
{
public:
	virtual ~IMediaPipeSolver() = default;
	virtual  bool IsInitialized() const = 0;
	virtual  void Initialize(const FAnimInstanceProxy* InAnimInstanceProxy) = 0;
	virtual void MapJoints(TSharedRef<FHumanoidBoneSettings>& Settings) = 0;
	virtual bool CacheBones(const FAnimationCacheBonesContext& Context) = 0;
	virtual bool Solve(const FMediaPipeFrame& MediaPipeFrame, FComponentSpacePoseContext& Output, float Alpha = 1.0f) = 0;
	virtual  void SetFilterParams(float KalmanParamQ, float KalmanParamR, float Smooth) = 0;
	virtual  void GetFilterParams(float& KalmanParamQ, float& KalmanParamR, float& Smooth) = 0;
	virtual void OnAnimModeChanged(EMediaPipeAnimMode Mode) = 0;
	virtual bool IsBoneCached() = 0;
	virtual bool IsDisabled() const = 0;
	virtual void SetDisabled(bool Disabled) = 0;
	virtual void ResetState(ESolverResetReason Reason) = 0;
	virtual void ClearFPSCounter() = 0;
	virtual float GetMediaPipeFPS() const = 0;
	virtual float GetFPS() const = 0;
	virtual float GetMinScoreThresh() const = 0;
	virtual void SetMinScoreThresh(float Threshold) = 0;
	virtual void SetDrawDebugEnabled(bool bEnabled) = 0;
	virtual bool IsDrawDebugEnabled() = 0;
	virtual void DebugDraw(FNodeDebugData& DebugData) = 0;
	virtual  void PerformCalibration(ECalibrationMethod Method) = 0;
	virtual void ExecuteCommand(const FName& Command) = 0;
	virtual void UnCalibration() = 0;
	
	virtual bool IsJointPrepared() = 0;
	
};
