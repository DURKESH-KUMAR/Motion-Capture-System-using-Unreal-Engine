// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once
#include "MediaPipeUtils.h"
#include "Math/MathFwd.h"
#include "MediaPipeLandmark.generated.h"

USTRUCT(BlueprintType)
struct MEDIAPIPE_API FMediaPipeLandmark
{
	GENERATED_BODY()

	FMediaPipeLandmark(){}

	/**
	 * Normalized coordinates aligned with the Unreal Engine, Y facing.
	 */
	UPROPERTY(Category = "Landmark", BlueprintReadOnly)
	FVector Pos = {0, 0, 0 };

	/**
	 * Coordinates same as MediaPipe (Origin data).
	 */
	UPROPERTY(Category = "Landmark", BlueprintReadOnly)
	FVector Origin = { 0, 0, 0 };

	//We dont use this, use Presence only.
	UPROPERTY(Category = "Landmark", BlueprintReadOnly)
	float Visibility = 0;

	UPROPERTY(Category = "Landmark", BlueprintReadOnly)
	float Presence = 0;

	UPROPERTY(Category = "Landmark", BlueprintReadOnly)
	bool bIsImageCoordinate = true;

	UPROPERTY(Category = "Landmark", BlueprintReadOnly)
	bool IsValid = true;

	static FMediaPipeLandmark CreateFromMediaPipeData(float X, float Y, float Z,
		bool bIsNormalizedLandmark = false,
		float Presence = 1.0f,
		float Visibility = 1.0f);
	
	void FillWithMediaPipeData(
		float X, float Y, float Z,
		bool bIsNormalizedLandmark = false,
		float InPresence = 1.0f,
		float InVisibility = 1.0f,
		const FSizeInt& ImageSize = FSizeInt::Zero()); 
 
	static FVector GetWorldPosition(const FVector& NormPos, int ImageWidth, int ImageHeight, float VerticalFOVDegrees = 60.0f, float DepthScale = 100.f);

	/**
	 * Got world position by GetWorldPosition, the method back to Pos
	 */
	static FVector WorldToNormPosition(const FVector& WorldPos, int ImageWidth, int ImageHeight, float VerticalFOVDegrees = 60.0f, float DepthScale = 100.f);

	float GetConfidence() const { return Presence; }

	FVector2D GetOrigin2D() const { return FVector2D{ Origin.X, Origin.Y }; }

	FVector2D GetOriginPixel2D(int ImageWidth, int ImageHeight) const
	{
		float PixelX = Origin.X * ImageWidth;
		float PixelY = Origin.Y * ImageHeight;
 
		return FVector2D(PixelX, PixelY);
	}

	FVector GetOriginPixel(int ImageWidth, int ImageHeight) const
	{
		float PixelX = Origin.X * ImageWidth;
		float PixelY = Origin.Y * ImageHeight; 
		float PixelZ = Origin.Z * ImageWidth;
		return FVector(PixelX, PixelY, PixelZ);
	}

	FMediaPipeLandmark(const FMediaPipeLandmark& Other)
		: Pos(Other.Pos),
		  Origin(Other.Origin),
		  Visibility(Other.Visibility),
		  Presence(Other.Presence),
		  bIsImageCoordinate(Other.bIsImageCoordinate),
		  IsValid(Other.IsValid)
	{
	}

	FMediaPipeLandmark(FMediaPipeLandmark&& Other) noexcept
		: Pos(std::move(Other.Pos)),
		  Origin(std::move(Other.Origin)),
		  Visibility(Other.Visibility),
		  Presence(Other.Presence),
		  bIsImageCoordinate(Other.bIsImageCoordinate),
		  IsValid(Other.IsValid)
	{
	}

	FMediaPipeLandmark& operator=(const FMediaPipeLandmark& Other)
	{
		if (this == &Other)
			return *this;
		Pos = Other.Pos;
		Origin = Other.Origin;
		Visibility = Other.Visibility;
		Presence = Other.Presence;
		bIsImageCoordinate = Other.bIsImageCoordinate;
		IsValid = Other.IsValid;
		return *this;
	}

	FMediaPipeLandmark& operator=(FMediaPipeLandmark&& Other) noexcept
	{
		if (this == &Other)
			return *this;
		Pos = std::move(Other.Pos);
		Origin = std::move(Other.Origin);
		Visibility = Other.Visibility;
		Presence = Other.Presence;
		bIsImageCoordinate = Other.bIsImageCoordinate;
		IsValid = Other.IsValid;
		return *this;
	}
};


using FMediaPipeLandmarkList = TArray<FMediaPipeLandmark>;
