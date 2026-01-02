// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "Templates/SharedPointer.h"

struct FMediaPipeLandmark;
class FMediaPipeConnector;

class MEDIAPIPE_API FMediaPipeConnection
{
public:
	FMediaPipeConnection() {}
	explicit FMediaPipeConnection(const TSharedRef<FMediaPipeConnector>& InConnector);
	void PutPoseLandmarks3D(const TSharedPtr<TArray<FMediaPipeLandmark>>& Landmarks) const;

	bool IsValid() const;

	FMediaPipeConnection(const FMediaPipeConnection& Other)
		: MPConnector(Other.MPConnector)
	{
	}

	FMediaPipeConnection(FMediaPipeConnection&& Other) noexcept
		: MPConnector(Other.MPConnector)
	{
	}

	FMediaPipeConnection& operator=(const FMediaPipeConnection& Other)
	{
		if (this == &Other)
			return *this;
		MPConnector = Other.MPConnector;
		return *this;
	}

	FMediaPipeConnection& operator=(FMediaPipeConnection&& Other) noexcept
	{
		if (this == &Other)
			return *this;
		MPConnector = Other.MPConnector;
		return *this;
	}

private:
	mutable  TWeakPtr<FMediaPipeConnector> MPConnector = nullptr;
};