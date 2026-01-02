// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GstSampleImpl.h"
#include "Engine/Texture2D.h"

#include "GstTextureContext.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct GSTREAMER_API FGstTextureContext
{
	GENERATED_BODY();

	FGstTextureContext() {}

	FGstTextureContext(UTexture2D* InTexture, TSharedPtr<IGstSample> InSample):
	Sample(InSample), Texture(InTexture)
	{}

	
	TSharedPtr<IGstSample> Sample = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="GST")
	UTexture2D* Texture = nullptr;
};
