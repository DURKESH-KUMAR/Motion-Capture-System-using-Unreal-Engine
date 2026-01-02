// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once

#include "CoreMinimal.h"
#include "FaceCanonicalPoints.h"
#include "MediaPipeAnimInstance.h"
#include "MediaPipeDebugDrawOptions.h"
#include "MediaPipeHandJoint.h"
#include "GameFramework/Character.h"
#include "MediaPipeDebugDrawer.generated.h"


UENUM(BlueprintType)
enum class EFaceDrawType : uint8
{
	None,
	FaceMesh,
	FaceGeometry
};

USTRUCT(BlueprintType)
struct MEDIAPIPEMOTION_API FLandmarkLine
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	int StartIndex = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	int EndIndex = -1;

	bool IsValid() const { return StartIndex >= 0 && EndIndex >=0 && StartIndex != EndIndex; }
};


UENUM()
enum class StickManPoints
{
	FilteredPosition,
	WorldPosition,
	MediaPipeRaw,
};

UCLASS(ClassGroup="MediaPipe", Blueprintable)
class MEDIAPIPEMOTION_API AMediaPipeDebugDrawer : public AActor
{
	GENERATED_BODY()

	
	
public:
	AMediaPipeDebugDrawer(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	bool bIsDisabled = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	TObjectPtr<AActor> MediaPipeAnimationInstanceByActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe | Draw")
	FMediaPipeDebugDrawOptions DrawOptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe | Draw")
	EFaceDrawType DrawFace = EFaceDrawType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe | Draw")
	bool bDrawStickMan = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe | Draw", meta=(EditCondition="bDrawStickMan"))
	float StickManScale = 170.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe | Draw", meta=(EditCondition="bDrawStickMan"))
	float FaceMeshScale = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe | Draw", meta=(EditCondition="bDrawStickMan"))
	StickManPoints StickManType = StickManPoints::FilteredPosition;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe | Draw")
	bool bDrawHandNormal = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe | Draw")
	bool bDrawPoseNormals = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe | Face")
	bool bDrawFaceMeshNormals = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe | Face")
	FTransform FaceGeometryTransform = FTransform::Identity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe | Face")
	FTransform FaceMeshTransform = FTransform::Identity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe | Face")
	bool  bDrawFace2D = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe | Face")
	TArray<int> HighlightFaceMeshLandmarks{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe | Face")
	TArray<FLandmarkLine> HighlightFaceMeshLines{};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe | Pose")
	TArray<EMediaPipePoseJoint> PoseJointNormalsToDraw{};
	

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	bool ReloadActor();
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaSeconds) override;
private:

	UPROPERTY(Transient)
	TWeakObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UPROPERTY(Transient)
	TWeakObjectPtr<UMediaPipeHolisticComponent> MediaPipeHolisticComponent;
	
	TWeakPtr<IHandSolver> HandSolver;
	TWeakPtr<IPoseSolver> PoseSolver;
	TWeakPtr<FMediaPipeAnimContext> AnimContext;

	FDelegateHandle FaceGeometryHandler;
	FDelegateHandle FaceMeshHandler;
	TSharedPtr<FMediaPipeFaceMesh> FaceMesh;
	
	FFaceCanonicalPoints FaceCanonicalPoints;

	TSharedPtr<TArray<FMediaPipeLandmark>> FaceMeshLandmarks;

	bool bIsInitialized;
	EFaceDrawType LatestDrawFaceValue = EFaceDrawType::None;

	void DrawPoseJointForward(const TArray<EMediaPipePoseJoint>& JointForwards) const;
	void DrawStickMan(bool bIsIncludeHands, const TArray<EMediaPipePoseJoint>& JointForwards) const;
	void DrawHandsLandmarks(EHandType HandType) const;
	void DrawFaceMesh();
	TArray<FMediaPipeLandmark>& GetFaceLandmarks() const;
	
	void HandleOutFaceGeometry(const TSharedPtr<FMediaPipeFaceMesh>& InFaceMesh,  const FMediaPipeSourceInfo& SourceInfo);
	void HandleOutFaceMesh(const TSharedPtr<TArray<FMediaPipeLandmark>>& InFaceMesh,  const FMediaPipeSourceInfo& SourceInfo);
	
	void RegisterMediaPipeHandle();
	void UnregisterMediaPipeHandle();
	void DrawHandJointForward(EHandType HandType, EMediaPipeHandJoint Joint) const;

	FVector GetStickManJointPosition(const EMediaPipePoseJoint Joint) const;
};
