// // Copyright (c) 2025 Anders Xiao. All rights reserved.
// // https://github.com/endink
// // Create: 2025-04-06

#pragma once
#include "IMediaPipeFeature.h"

class MEDIAPIPE_API IMediaPipeHolisticFeatureRegistry
{
public:
	virtual ~IMediaPipeHolisticFeatureRegistry() = default;
	virtual bool IsFeatureEnabled(EMediaPipeFeatures Feature) const = 0;
	virtual TSharedPtr<IMediaPipeFeature> FindFeature(EMediaPipeFeatures Feature) const = 0;
	virtual void RegisterFeature(EMediaPipeFeatures Feature, TSharedPtr<IMediaPipeFeature> Alternative) = 0;
	virtual void UnregisterFeature(EMediaPipeFeatures Feature) = 0;
};
