// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once
#include "CoreMinimal.h"
#include "Math/Color.h"
#include "Engine/World.h"

class MEDIAPIPE_API DebugDrawer
{
public:
	inline static ESceneDepthPriorityGroup DefaultDepth = SDPG_Foreground;
	static void DrawLines(const TWeakObjectPtr<const UWorld>, const FColor& Color, const float& LineThickness,
	                          const TArray<FVector>& Points, const TArray<int>& LinePointIndices, bool bClosePath = false);


	static void DrawLine(const TWeakObjectPtr<const UWorld>, const FVector& Start, const FVector& Finish,
		const FLinearColor& Color= FColor(0, 255, 0), float Duration = -1.0f, float Thickness = 1.0f);

	static void DrawPoint(const TWeakObjectPtr<const UWorld> World, const FVector& Position, const FColor& PointColor = FColor(0, 255,0), float Size = 5, float Duration = -1.0f);

	static void DrawSphere(const TWeakObjectPtr<const UWorld> World, const FVector& Center, const FLinearColor& Color = FColor(0, 255, 0),
		float Radius = 15.0f, int32 Segments = 12, float Duration = -1.0f, float Thickness = 0.75f);

	static void DrawString(const TWeakObjectPtr<const UWorld> World, const FVector& Location, const FString& Text,  const FColor& Color, float Duration = .0f, AActor* BaseActor = nullptr);

	static void DrawCircle(const TWeakObjectPtr<const UWorld> World, const FVector& Center, const FVector& PlaneNormal, float Size = 100.0f,
		const FLinearColor& Color = FColor(255, 0, 255, 90), float Duration = -1.0f);
	
	static void DrawPlane(const TWeakObjectPtr<const UWorld> World, const FVector& PlaneBase, const FVector& PlaneNormal, float Size = 100.0f,
		const FLinearColor& Color = FColor(255, 0, 255, 90), bool bDrawNormal = true, float Duration = -1.0f);

	// Draws a direction vector, starting at base, with some pre-decided length. Set length to a negative
	static void DrawVector(const TWeakObjectPtr<const UWorld> World, const FVector& Base, FVector Direction,
		const FLinearColor& Color = FColor(255, 0, 0), float Length = 50.0f, 
		float Duration = -1.0f, float Thickness = 1.0f);
};

