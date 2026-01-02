// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "GroundSolveSettings.h"
#include "ISolverProvider.h"

class IGroundSolver : public ISolverProvider
{
public:
	virtual ~IGroundSolver() override = default;
	virtual FGroundSolveSettings& GetSettings() = 0;
};
