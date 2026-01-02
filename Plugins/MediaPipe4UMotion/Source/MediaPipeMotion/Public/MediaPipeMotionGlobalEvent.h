// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "MediaPipeHolisticComponent.h"
#include "MediaPipeGlobalEvents.h"

class MEDIAPIPEMOTION_API FMediaPipeMotionGlobalEvent
{
	
	DECLARE_GLOBAL_EVENT_OneParam(FMediaPipeMotionGlobalEvent, MediaPipeHolisticUninitialized, UMediaPipeHolisticComponent*, HolisticComponent)
	DECLARE_GLOBAL_EVENT_OneParam(FMediaPipeMotionGlobalEvent, MediaPipeHolisticInitialized, UMediaPipeHolisticComponent*, HolisticComponent)
public:
	FMediaPipeMotionGlobalEvent();
	
};

extern MEDIAPIPEMOTION_API FMediaPipeMotionGlobalEvent* GMediaPipeMotionEvents;