// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "DampingMode.h"
#include "RuntimeDamper.h"
#include "MediaPipeAnimExtensionActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "VectorDamper.h"

class MEDIAPIPEMOTION_API FRuntimeVectorDamper : public RuntimeDamper<FVector, FVectorSpringState>
{
public:
	FRuntimeVectorDamper(){}
	bool bIsUserDefined = false;

	void Update(const FVectorDamper& InDamper);
	
	void UpdateStiffness(const float InStiffness);

	bool NeedSwingLimit() const;

	void SetSwingLimitation(float LimitationValue);
	float GetStiffness() const;

	FVector InterpTo(const FVector& Target, float DeltaSeconds, EDampingMode Mode = EDampingMode::Spring);
	
	
	float SwingX = 0;
	float SwingY = 0;
	float SwingZ = 0;

private:
	float Stiffness = 450.0f;
	float Damping = 1.0f;
};
