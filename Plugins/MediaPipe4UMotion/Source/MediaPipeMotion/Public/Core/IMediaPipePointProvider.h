// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once
#include "CoreMinimal.h"

class MEDIAPIPEMOTION_API IMediaPipePointProvider
{
public:
	virtual ~IMediaPipePointProvider() = default;
	virtual  FVector GetPosition() const = 0;
};
