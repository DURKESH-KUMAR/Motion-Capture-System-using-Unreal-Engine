// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "CoreMinimal.h"
#include "DampingMode.h"

template<typename TValue, typename TSpringState>
class RuntimeDamper
{
public:
	TOptional<TValue>& GetLatestValue(EDampingMode Mode = EDampingMode::Spring)
	{
		auto mode = NormalizeMode(Mode);
		return LatestValues.FindOrAdd(mode);
	}
	
	void RequestReset()
	{
		bRequestReset = true;
	}
	

	bool IsReady() const
	{
		return !LatestValues.IsEmpty();
	}

	void SetAlpha(float InAlpha)
	{
		Alpha = InAlpha;
	}

	void ResetState()
	{
		LatestValues.Reset();
		SpringState.Reset();
		bRequestReset = false;
	}
	TSpringState SpringState;
protected:
	bool bRequestReset = false;
	float Alpha = 0.3f;
	TMap<EDampingMode, TOptional<TValue>> LatestValues;
	
	static EDampingMode NormalizeMode(EDampingMode Mode)
	{
		switch (Mode)
		{
		case EDampingMode::EaseIn: ;
		case EDampingMode::EaseOut:
			return EDampingMode::EaseIn;
		case EDampingMode::CircularIn: 
			return EDampingMode::CircularIn;
		case EDampingMode::CircularOut: 
			return EDampingMode::CircularOut;
		default:
			return Mode;
		}
	}
};
