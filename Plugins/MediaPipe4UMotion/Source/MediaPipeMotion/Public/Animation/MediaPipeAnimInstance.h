// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once

#include "CoreMinimal.h"
#include "BonePresets.h"
#include "IBoneSettingsProvider.h"
#include "IHandSolver.h"
#include "CalibrationPolicy.h"
#include "ILocationSolver.h"
#include "IPoseSolver.h"
#include "MediaPipeAnimContext.h"
#include "MediaPipeAnimMode.h"
#include "MediaPipeAutoConnect.h"
#include "MediaPipeSource.h"
#include "MediaPipeHolisticComponent.h"
#include "MediaPipeRemapAsset.h"
#include "Animation/AnimInstance.h"
#include "Head/IHeadSolver.h"
#include "IGroundSolver.h"
#include "LiveLinkTypes.h"
#include "SolverResetReason.h" 
#include "MediaPipeAnimInstance.generated.h"
/**
 * 
 */
UCLASS(BlueprintType)
class MEDIAPIPEMOTION_API UMediaPipeAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UMediaPipeAnimInstance();

	TSharedPtr<ILocationSolver> GetLocationSolver() { return LocationSolver; }
	TSharedPtr<IPoseSolver> GetPoseSolver() { return PoseSolver; }
	TSharedPtr<IHandSolver> GetHandsSolver() { return HandsSolver; }
	TSharedPtr<IHeadSolver> GetHeadSolver() { return HeadSolver; }
	TSharedPtr<IGroundSolver> GetGroundIKSolver() { return GroundIKSolver; }

	const TSharedPtr<FMediaPipeAnimContext>& GetContext() const;

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	void GetSolverFPS(float& AnimationFPS, float& MediaPipeFPS);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MediaPipe")
	EMediaPipeAnimMode Mode = EMediaPipeAnimMode::FullBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MediaPipe")
	bool ResetOnPipelineStopped = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MediaPipe")
	bool bSolveFingers = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MediaPipe")
	bool bSolveHeadFromFaceMesh = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MediaPipe")
	bool bSolveLocation = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MediaPipe")
	float MinPoseScoreThresh = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MediaPipe")
	float MinHandScoreThresh = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MediaPipe")
	float MinFaceScoreThresh = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MediaPipe")
	bool bTwistCorrectionEnabled = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MediaPipe")
	bool bSolveLocationOnStaticImage = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MediaPipe")
	EMediaPipeAutoConnect AutoConnectToMediaPipe = EMediaPipeAutoConnect::Enabled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MediaPipe|LiveLink")
	FLiveLinkSubjectName LiveLinkSubject = FLiveLinkSubjectName(FName(TEXT("MediaPipe4U")));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MediaPipe|LiveLink")
	bool bLiveLinkEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MediaPipe|Debug")
	bool bDebugDraw = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MediaPipe|Calibration", meta = (PinShownByDefault, ClampMin=1.f, ClampMax=60.f))
	int CalibrationCountdownSeconds = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MediaPipe|Calibration")
	ECalibrationPolicy CalibrationPolicy = ECalibrationPolicy::Manual;

	FVector OriginHipLocation = FVector::Zero();
	FVector OriginActorLocation = FVector::Zero();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	EBonePresets BonePreset = EBonePresets::UE5;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MediaPipe",  meta=(EditCondition="BonePreset == EBonePresets::Custom"))
	TObjectPtr<UMediaPipeRemapAsset> BoneRemap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MediaPipe")
	TObjectPtr<UPoseAsset> PoseAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MediaPipe")
	FName PoseForInit = NAME_None;
	
	virtual void NativeBeginPlay() override;

	TWeakPtr<FHumanoidBoneSettings> GetBoneSettings();

	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	bool IsMediaPipeRunning();

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	bool IsPaused() const;

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	void Pause() const;

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	void Resume() const;

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	bool ConnectToMediaPipeInLevel();

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	bool ConnectToMediaPipe(UMediaPipeHolisticComponent* MediaPipeComponent);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	bool IsMediaPipeConnected() const;

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	void DisconnectFromMediaPipe();

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	bool LoadBoneSettingsFromJsonContent(const FString& JsonContent);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	bool LoadBoneSettingsFromJsonFile(const FString& FilePath);

	UFUNCTION(BlueprintCallable, Category="MediaPipe|Calibration")
	void CalibratePose();

	UFUNCTION(BlueprintCallable, Category="MediaPipe|Calibration")
	void UnCalibratePose();

	UFUNCTION(BlueprintCallable, Category="MediaPipe|Calibration")
	void CalibrateLocation();

	UFUNCTION(BlueprintCallable, Category="MediaPipe|Calibration")
	void UnCalibrateLocation();

	UFUNCTION(BlueprintCallable, Category="MediaPipe|Calibration")
	int GetCalibrationRemainingSeconds();
	
	UFUNCTION(BlueprintCallable, Category="MediaPipe|Calibration")
	void StartCalibrationCountdown(int CountdownSeconds = 5);

	UFUNCTION(BlueprintCallable, Category="MediaPipe|Calibration")
	void CancelCalibrationCountdown();
	
	virtual bool LoadBoneSettings(TSharedPtr<IBoneSettingsProvider> = nullptr);
protected:
	void PrepareSolvers(IBoneSettingsProvider* Provider);
	void TurnOnMediaPipeEnvironment(UMediaPipeHolisticComponent* InComponent); 
	TSharedRef<FHumanoidBoneSettings> BoneSettings = MakeShared<FHumanoidBoneSettings>();

	virtual void OnBoneSettingsApplied(FHumanoidBoneSettings& Settings) {};

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUninitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativePostEvaluateAnimation() override;

	 
	virtual void HandlePoseOut(const TSharedPtr<TArray<FMediaPipeLandmark>>& Landmarks, const FMediaPipeSourceInfo& SourceInfo);
	virtual void HandlePoseWorldOut(const TSharedPtr<TArray<FMediaPipeLandmark>>& Landmarks, const FMediaPipeSourceInfo& SourceInfo);
	virtual void HandleFaceGeometryOut(const TSharedPtr<FMediaPipeFaceMesh>& FaceGeometry, const FMediaPipeSourceInfo& SourceInfo);
	virtual void HandleFaceLandmarksOut(const TSharedPtr<TArray<FMediaPipeLandmark>>& Landmarks, const FMediaPipeSourceInfo& SourceInfo);
	virtual void HandleLeftHandOut(const TSharedPtr<TArray<FMediaPipeLandmark>>& Landmarks, const FMediaPipeSourceInfo& SourceInfo);
	virtual void HandleRightHandOut(const TSharedPtr<TArray<FMediaPipeLandmark>>& Landmarks, const FMediaPipeSourceInfo& SourceInfo);

	virtual void HandleMediaPipeHolisticStopping(UMediaPipeHolisticComponent* Component);
	virtual void HandleMediaPipeHolisticStopped(UMediaPipeHolisticComponent* Component);
	virtual void HandleBeforeMediaPipeHolisticStart(FMediaPipeTaskContext& Context);
	virtual void HandleMediaPipeHolisticStarted(UMediaPipeHolisticComponent* Component);
	virtual void HandleMediaPipeHolisticUninitialized(UMediaPipeHolisticComponent* Component);
	virtual void HandleMediaPipeHolisticInitialized(UMediaPipeHolisticComponent* Component);
	void ResetMediaPipeState(ESolverResetReason Reason);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	void ResetAllSolvers(ESolverResetReason Reason);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	void EnableAllSolvers(bool bIsEnabled);

private:
	bool IsCountdownCalibrationCompleted();
	void PerformCalibrationInternal(ECalibrationMethod Reason);
	
	UPROPERTY(Transient)
	TWeakObjectPtr<UMediaPipeHolisticComponent> MediaPipeHolisticComponent;

	TSharedPtr<FMediaPipeSource> GetMediaPipeSource() const;
	bool bAutoReconnect = false;
	void RegisterEventHandler();
	void UnRegisterEventHandler() const;

	//int CalibrationSecondsElapsed = 0;
	float CalibrationSecondsRemaining = 0;
	bool bCountdownCalibrationCancelled = false;
 
	void DrawIKChain(const FVector& A, const FVector& B, const FVector& C);

	TSharedPtr<FMediaPipeAnimContext> SharedContext;
	
	TSharedPtr<IPoseSolver> PoseSolver;
	TSharedPtr<ILocationSolver> LocationSolver;
	TSharedPtr<IHandSolver> HandsSolver;
	TSharedPtr<IHeadSolver> HeadSolver;
	TSharedPtr<IGroundSolver> GroundIKSolver;

	TArray<TSharedPtr<ISolverProvider>> AllProviders;
	mutable FCriticalSection EventHandlingCS;

	static void UpdateSolverEnabled(TWeakObjectPtr<UMediaPipeHolisticComponent>Component, UMediaPipeAnimInstance* AnimInstance);
};




