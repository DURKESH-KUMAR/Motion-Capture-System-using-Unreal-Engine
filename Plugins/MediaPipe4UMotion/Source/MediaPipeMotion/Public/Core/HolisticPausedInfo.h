// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "MediaPipeImageSource.h"
#include "WebcamParams.h"
#include "UObject/WeakObjectPtrTemplates.h"

class IMediaPipeImageSource;

struct MEDIAPIPEMOTION_API FHolisticPausedInfo
{
	TWeakObjectPtr<UObject> ImageSource = nullptr;
	bool bIsWebcamImageSource = false;
	FWebcamParams WebcamRequestParams{};
	bool bNeedRecovery = false;
	int64 SessionId = 0;
};
