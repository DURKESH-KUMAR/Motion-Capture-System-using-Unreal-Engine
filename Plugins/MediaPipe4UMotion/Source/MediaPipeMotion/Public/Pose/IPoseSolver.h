// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once
#include "IMediaPipeSolver.h"
#include "ISolverProvider.h"
#include "AngularDamper.h"
#include "MediaPipePoseJoint.h"
#include "PoseCalibrationFlags.h"
#include "PoseSolverLockSettings.h"
#include "HumanoidKeyJoint.h"
#include "PoseOptimizationSettings.h"
#include "SpringDampingSettings.h"

class MEDIAPIPEMOTION_API IPoseSolver : public virtual ISolverProvider
{
public:
	virtual  FPoseSolverLockSettings& GetLocks() = 0;
	virtual FRotationLockConfig& GetUpperBodyLocks() = 0;
	virtual  void ApplyLocks() = 0;

	virtual void UseLegIK(bool bUse) = 0;
	virtual void UseArmIK(bool bUse) = 0;

	virtual bool IsLegIKUsed() const = 0;
	virtual bool IsArmIKUsed() const = 0;

	virtual void GetBodyAngleDegrees(float& Pitch, float& Yaw, float& Roll) const = 0;
	
	virtual bool GetOptimize() = 0;
	virtual void SetOptimize(bool Enabled) = 0;

	virtual FPoseOptimizationSettings& GetOptimizationSettings() = 0;
	
	virtual bool HasCalibrationFlag(EPoseCalibrationFlags Flag) const = 0;
	virtual uint8 GetCalibrationFlags() = 0;
	virtual void SetCalibrationFlags(uint8 Flags) = 0;
	virtual void AddSecondarySmooth(EMediaPipePoseJoint Joint, float Smooth) = 0;
	virtual void RemoveSecondarySmooth(EMediaPipePoseJoint Joint) = 0;

	virtual FSpringDampingSettings& GetFeetSpringSettings() = 0;
	virtual FSpringDampingSettings& GetHandsSpringSettings() = 0;
	
	
	virtual void ClearAllSecondarySmooth() = 0;
	virtual bool IsCountdownCalibrationEnabled() const = 0;
	virtual void SetIsCountdownCalibrationEnabled(bool bEnabled) = 0;
	virtual bool IsCalibrated() const = 0;

	virtual bool IsFixMediaPipePose() const = 0;
	virtual void SetFixMediaPipePose(bool bEnabled) = 0;
	
	// virtual TMap<EHumanoidBodyPart, FAngularDamper>& GetJointRotationDampers() = 0;
};
