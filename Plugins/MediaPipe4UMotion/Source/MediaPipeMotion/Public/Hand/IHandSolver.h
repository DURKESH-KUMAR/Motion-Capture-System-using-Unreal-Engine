// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink


#pragma once
#include "HandLostPolicy.h"
#include "IMediaPipeSolver.h"
#include "ISolverProvider.h"
#include "RunTimeTypes.h"
#include "MediaPipeFrame.h"
#include "Animation/AnimNodeBase.h"

class IHandSolver  :  public virtual  IMediaPipeSolver, public virtual ISolverProvider
{
public:
	virtual bool SolveSingleHand(const EHandType HandType, FMediaPipeFrame& MediaPipeFrame, FComponentSpacePoseContext& Output, float Alpha = 1.0f) const = 0;
	virtual bool GetOptimize() = 0;
	virtual void SetOptimize(bool Enabled) = 0;
	virtual bool IsResetPointEnabled() = 0;
	virtual void SetResetPointEnabled(bool bEnabled) = 0;
	virtual float GetResetPoint() = 0;
	virtual void SetResetPoint(float Point) = 0;
	virtual void SetHandResetSmooth(float Smooth) = 0;
	virtual void SetHandLostPolicy(EHandLostPolicy Policy) = 0;
	virtual void SetHandLostDuration(float Seconds) = 0;
	virtual uint32 GetWristStiffness() const = 0;
	virtual void SetWristStiffness(uint32 Stiffness) = 0;
};