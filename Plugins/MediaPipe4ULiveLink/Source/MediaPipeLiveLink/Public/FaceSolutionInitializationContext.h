// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "CoreMinimal.h"
#include "ParameterValue.h"
#include "UObject/WeakObjectPtr.h"

class AMediaPipeFaceLinkActor;
class UMediaPipeHolisticComponent;

struct MEDIAPIPELIVELINK_API FFaceSolutionInitializationContext
{
	TWeakObjectPtr<UMediaPipeHolisticComponent> MediaPipeHolisticComponent;
	bool bIsStaticImage = false;
	TMap<FName, FParameterValue>  Parameters;
	TWeakObjectPtr<AMediaPipeFaceLinkActor> LiveLinkActor;

	FFaceSolutionInitializationContext() {}

	FFaceSolutionInitializationContext(const FFaceSolutionInitializationContext& Other)
		: MediaPipeHolisticComponent(Other.MediaPipeHolisticComponent),
		  bIsStaticImage(Other.bIsStaticImage),
		  Parameters(Other.Parameters),
		  LiveLinkActor(Other.LiveLinkActor)
	{
	}

	FFaceSolutionInitializationContext(FFaceSolutionInitializationContext&& Other) noexcept
		: MediaPipeHolisticComponent(std::move(Other.MediaPipeHolisticComponent)),
		  bIsStaticImage(Other.bIsStaticImage),
		  Parameters(std::move(Other.Parameters)),
		  LiveLinkActor(std::move(Other.LiveLinkActor))
	{
	}

	FFaceSolutionInitializationContext& operator=(const FFaceSolutionInitializationContext& Other)
	{
		if (this == &Other)
			return *this;
		MediaPipeHolisticComponent = Other.MediaPipeHolisticComponent;
		bIsStaticImage = Other.bIsStaticImage;
		Parameters = Other.Parameters;
		LiveLinkActor = Other.LiveLinkActor;
		return *this;
	}

	FFaceSolutionInitializationContext& operator=(FFaceSolutionInitializationContext&& Other) noexcept
	{
		if (this == &Other)
			return *this;
		MediaPipeHolisticComponent = std::move(Other.MediaPipeHolisticComponent);
		bIsStaticImage = Other.bIsStaticImage;
		Parameters = std::move(Other.Parameters);
		LiveLinkActor = std::move(Other.LiveLinkActor);
		return *this;
	}
};
