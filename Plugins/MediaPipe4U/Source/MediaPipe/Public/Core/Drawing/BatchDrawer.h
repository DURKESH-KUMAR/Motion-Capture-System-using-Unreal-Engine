// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "Runtime/Core/Public/Math/Color.h"
#include "Runtime/Core/Public/Math/Vector.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Public/BonePose.h"
#include "CoreMinimal.h"
#include "IDrawable.h"

class MEDIAPIPE_API FBatchDrawer
{
public:
	void AddLine(const FVector& Start, const FVector& Finish, const FLinearColor& Color= FColor(0, 255, 0), float Thickness = 1.0f, float Duration = -1.0f);

	void AddSphere(const FVector& Center, const FLinearColor& Color = FColor(0, 255, 0), float Radius = 15.0f, int32 Segments = 12, float Thickness = 0.75f, float Duration = -1.0f);

	void AddString(const FVector& Location, const FString& Text, const FColor& Color, AActor* BaseActor, float Duration = 0.0f);

	void AddPlane(const FVector& PlaneBase, const FVector& PlaneNormal, float Size = 100.0f,
		const FLinearColor& Color = FColor(255, 0, 255, 90), bool bDrawNormal = true, float Duration = -1.0f);

	// Draws a direction vector, starting at base, with some pre-decided length. Set length to a negative
	void AddVector(const FVector& Base, FVector Direction,
		const FLinearColor& Color = FColor(255, 0, 0), float Length = 50.0f, 
		float Thickness = 1.0f, float Duration = -1.0f);

	

	void AddDrawable(const TSharedPtr<IDrawable>& Drawable);
	
	void Draw(UWorld* World, bool bClear = true);
	void Clear();
private:
	TArray<TSharedPtr<IDrawable>> Elements;
};
