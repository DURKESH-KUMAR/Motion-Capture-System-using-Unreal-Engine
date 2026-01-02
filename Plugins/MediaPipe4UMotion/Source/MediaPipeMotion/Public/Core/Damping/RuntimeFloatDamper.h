// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "CoreMinimal.h"
#include "FloatDamer.h"
#include "RuntimeDamper.h"
#include "Kismet/KismetMathLibrary.h"


class MEDIAPIPEMOTION_API FRuntimeFloatDamper : public RuntimeDamper<float, FFloatSpringState>
{ 
public:
	FRuntimeFloatDamper(){}
	void Update(const FFloatDamer& Damper);
	float InterpTo(float TargetValue, float DeltaSeconds, EDampingMode Mode = EDampingMode::Spring);

	bool bIsUserDefined = false;
private:
	float Stiffness = 450.0f;
	float Damping = 1.0f;
};
