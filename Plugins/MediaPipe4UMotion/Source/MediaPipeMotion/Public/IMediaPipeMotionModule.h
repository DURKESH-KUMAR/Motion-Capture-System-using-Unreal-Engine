// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

class MEDIAPIPEMOTION_API IMediaPipeMotionModule : public IModuleInterface
{
public:
	static IMediaPipeMotionModule& Get()
	{
		return FModuleManager::LoadModuleChecked<IMediaPipeMotionModule>("MediaPipeMotion");
	}

	static bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("MediaPipeMotion");
	}
};
