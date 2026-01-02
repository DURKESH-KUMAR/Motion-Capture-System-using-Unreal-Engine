// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "Engine/World.h"

class IDrawable
{
public:
	virtual ~IDrawable() = default;
	virtual void Draw(UWorld* World) = 0;
};
