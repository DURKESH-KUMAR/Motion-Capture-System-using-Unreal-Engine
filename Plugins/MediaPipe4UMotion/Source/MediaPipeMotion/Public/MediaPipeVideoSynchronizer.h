// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once

#include "CoreMinimal.h"
#include "MediaPipeAnimMode.h"
#include "GameFramework/Character.h"
#include "MediaPipeHolisticComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include "MediaPipeVideoSynchronizer.generated.h"

UCLASS(Blueprintable, BlueprintType)
class MEDIAPIPEMOTION_API AMediaPipeVideoSynchronizer : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMediaPipeVideoSynchronizer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe Video Synchronizer|Components")
	TObjectPtr<AStaticMeshActor> VideoPanel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MediaPipe Video Synchronizer|Components")
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe Video Synchronizer|Components")
	TObjectPtr<ACharacter> Character;

	UFUNCTION(BlueprintCallable, Category="MediaPipe Video Synchronizer")
	void Run();

	void SetupPanel(float PanelDistance);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe Video Synchronizer")
	float DepthInCM = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe Video Synchronizer")
	float FocalLength = 350;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe Video Synchronizer")
	bool bSetupToViewPort = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe Video Synchronizer")
	FVector CharacterOffset = FVector::Zero();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe Video Synchronizer")
	UMaterialInterface* Material;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe Video Synchronizer")
	EMediaPipeAnimMode Mode = EMediaPipeAnimMode::UpperBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe Video Synchronizer")
	int32 VideoPersonTall = 180;

protected:
	UFUNCTION()
	void OnMediaPipeTextureCreated(UTexture2D* NewTexture, int TextureWidth, int TextureHeight);

	TWeakObjectPtr<UMediaPipeHolisticComponent> HolisticComponent;
	
	void AlignCamera(float VideoFOV, float AspectRatio);
	void OnPoseLandmarks(const TSharedPtr<TArray<FMediaPipeLandmark>>& Array, const FMediaPipeSourceInfo& MediaPipeSourceInfo);
	UFUNCTION()
	void OnMediaPipeStopped();
	void OnMediaPipeReady(UMediaPipeHolisticComponent* MediaPipeHolisticComponent);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	
	int ImageWidth = 0;
	int ImageHeight = 0;

	FVector2D NormalizedToPixel(const FVector& NormalizedPoint);
	bool bPanelSetup = true;

	void AlignCharacterToCamera(const TSharedPtr<TArray<FMediaPipeLandmark>>& Landmarks, int32 VideoWidth, int32 VideoHeight, float ReferenceHeight, float CameraDistance);;
	
	static FVector2D VideoPixelToPanel(float PixelX, float PixelY, float VideoWidth, float VideoHeight, 
	                                   float PanelWidth, float PanelHeight);

	FVector PanelToWorld(FVector2D PanelCoord);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	static bool GetBodyHeightInPixel(const TArray<FMediaPipeLandmark>& PoseLandmarks, int ImageWidth, int ImageHeight, float& BodyHeight);

	static bool GetBodyHeightInPixelByShoulder(const TArray<FMediaPipeLandmark>& PoseLandmarks, int ImageWidth, int ImageHeight, float& BodyHeight);

private:
	TQueue<TSharedPtr<TArray<FMediaPipeLandmark>>> PoseLandmarks;
	float InitCharacterToPanelDistance = 0;
	float InitCharacterToCameraDistance = 0;

	FTransform CameraTransform;
	FTransform CharacterTransform;
	FTransform PanelTransform;
};
