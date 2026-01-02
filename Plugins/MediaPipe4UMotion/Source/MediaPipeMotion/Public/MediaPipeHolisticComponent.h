// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once

#include "CoreMinimal.h"
#include "WebcamParams.h"
#include "HolisticPausedInfo.h"
#include "MediaPipeFaceMesh.h"
#include "MediaPipeHolisticOptions.h"
#include "MediaPipeImageSource.h"
#include "MediaPipeLandmark.h"
#include "MediaPipeSourceInfo.h"
#include "VideoDisplay.h"
#include "DynamicTexture.h"
#include "IMediaPipeHolisticConnector.h"
#include "WebcamImageSourceComponent.h"
#include "Components/ActorComponent.h"
#include "MediaPipeHolisticComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnVideoTextureCreated, UTexture2D*, NewTexture, int, TextureWidth, int, TextureHeight);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMediaPipeLifeCycle);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAsyncTaskResult);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLandmarks, const TArray<FMediaPipeLandmark>&, Landmarks, const FMediaPipeSourceInfo&, ImageSource);

class FMediaPipeConnector;
class SMediaPipeCapturePanel;
class IUmpPacketCallback;
class UMediaPipeHolisticComponent;
class FStartImageSourceAction;
class StartHolisticComponentAsyncTask;
class UStopHolisticComponentAsyncTask;

USTRUCT(BlueprintType)
struct MEDIAPIPEMOTION_API FMediaPipeTaskContext
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MediaPipe", Transient)
	UMediaPipeHolisticComponent* MediaPipeHolisticComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MediaPipe", Transient)
	TScriptInterface<IMediaPipeImageSource> ImageSourceInfo{};

	IMediaPipeImageSource* NativeImageSourceInfo = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MediaPipe", Transient)
	FMediaPipeHolisticOptions Options;
};

DECLARE_DELEGATE_OneParam(FOnStartAsyncCompleted, bool);

UCLASS(ClassGroup="MediaPipe", meta=(BlueprintSpawnableComponent))
class MEDIAPIPEMOTION_API UMediaPipeHolisticComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	typedef TMap<FName, float> MediaPipeClassifications;
	
	DECLARE_EVENT_ThreeParams(UMediaPipeHolisticComponent, FVideoTextureCreatedEvent, UTexture2D*, int, int);
	DECLARE_EVENT_OneParam(UMediaPipeHolisticComponent, FBeforeMediaPipeHolisticStart, FMediaPipeTaskContext&);
	DECLARE_EVENT_OneParam(UMediaPipeHolisticComponent, FOnMediaPipeHolisticStateChanged, UMediaPipeHolisticComponent*);
	DECLARE_EVENT_TwoParams(UMediaPipeHolisticComponent, FLandmarksOutEvent, const TSharedPtr<TArray<FMediaPipeLandmark>>&, const FMediaPipeSourceInfo&);
	DECLARE_EVENT_TwoParams(UMediaPipeHolisticComponent, FaceGeometryOutEvent, const TSharedPtr<FMediaPipeFaceMesh>&, const FMediaPipeSourceInfo&);
	DECLARE_EVENT_TwoParams(UMediaPipeHolisticComponent, FClassificationsOutEvent, const TSharedPtr<MediaPipeClassifications>&, const FMediaPipeSourceInfo&);
	
	
	//multi_face_geometry
	FLandmarksOutEvent& PoseLandmarksEventTrigger() { return PoseLandmarksEvent; }
	FLandmarksOutEvent& LeftHandLandmarksEventTrigger() { return LeftHandLandmarksEvent; };
	FLandmarksOutEvent& RightHandLandmarksEventTrigger() { return RightHandLandmarksEvent; }
	FLandmarksOutEvent& FaceLandmarksEventTrigger() { return FaceLandmarksEvent; }
	FLandmarksOutEvent& PoseWorldLandmarksEventTrigger() { return PoseWorldLandmarksEvent; }
	FaceGeometryOutEvent& FaceGeometryEventTrigger() { return FaceGeometryEvent; }
	FClassificationsOutEvent& FaceBlendShapesEventTrigger() { return FaceBlendShapesEvent; }
	FVideoTextureCreatedEvent& VideoTextureCreatedEventTrigger() { return VideoTextureCreatedEvent; }


	FOnMediaPipeHolisticStateChanged& OnMediaPipeHolisticStoppingTrigger() { return OnStoppingEvent; }
	FOnMediaPipeHolisticStateChanged& OnMediaPipeHolisticStoppedTrigger() { return OnStoppedEvent; }
	FBeforeMediaPipeHolisticStart& BeforeMediaPipeHolisticStartTrigger() { return BeforeStartEvent;  }
	FOnMediaPipeHolisticStateChanged& OnMediaPipeHolisticStartFailedTrigger() { return OnStartFailedEvent;  }
	FOnMediaPipeHolisticStateChanged& OnMediaPipeHolisticStartedTrigger() { return OnStartedEvent; }
	
	// Sets default values for this component's properties
	UMediaPipeHolisticComponent();
	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	IMediaPipeImageSource* GetCurrentImageSource() const;

	UFUNCTION(BlueprintPure, Category="MediaPipe")
	bool IsNativeImageSource() const;

	UFUNCTION(BlueprintPure, Category="MediaPipe")
	bool IsWebcamCapture();

	UFUNCTION(BlueprintPure, Category = "MediaPipe")
	bool IsVideoTextureAvailable();

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	UTexture2D* GetVideoTexture();

	UFUNCTION(BlueprintPure, Category="MediaPipe") 
	bool GetImageSourceFPS(float& SourceFrameRate, float& StreamingFrameRate) const;


	UFUNCTION(Category="MediaPipe", BlueprintPure)
	FWebcamParams  GetCurrentCameraParams();
	
	UFUNCTION(Category="MediaPipe", BlueprintCallable, meta=(ReturnDisplayName="Success"))
	bool StartCamera(int DeviceId = 0, int ResolutionX = 1280, int ResolutionY = 720, int FPS = 30);

	UFUNCTION(Category="MediaPipe", BlueprintCallable, meta=(ReturnDisplayName="Success"))
	bool StartImageSource(const TScriptInterface<IMediaPipeImageSource>& ImageSource);

	UFUNCTION(Category="MediaPipe", BlueprintCallable)
	float GetSourceTextureAspectRatio();

	UFUNCTION(Category="MediaPipe", BlueprintCallable)
	virtual void Stop();

	UFUNCTION(Category="MediaPipe", BlueprintPure)
	bool IsRunning() const;

	UFUNCTION(Category="MediaPipe", BlueprintPure)
	void GetFrameSize(int& FrameWidth, int& FrameHeight) const;

	UPROPERTY(Category="MediaPipe", BlueprintReadWrite, EditAnywhere)
	EVideoDisplay VideoDisplay = EVideoDisplay::Annotated;

	UPROPERTY(Category="MediaPipe", BlueprintReadWrite, EditAnywhere, meta = (EditCondition = "VideoDisplay == EVideoDisplay::Annotated"))
	EMediaPipeAnnotations OverlayAnnotations = EMediaPipeAnnotations::PoseTracking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	FMediaPipeHolisticOptions Options;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="MediaPipe|Image Source", Transient)
	FMediaPipeSourceInfo MediaPipeSourceInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe")
	int GraphTimeoutSeconds = 10;

	UFUNCTION(Category="MediaPipe", BlueprintPure)
	bool IsStaticImageSource() const;

	bool StartCustomConnector(const TSharedPtr<IMediaPipeHolisticConnector>& Connector);
	TFuture<bool> StartCustomConnectorAsync(const TSharedPtr<IMediaPipeHolisticConnector>& Connector);
	
	bool StartImageSource(IMediaPipeImageSource* ImageSource);
	TFuture<bool> StartImageSourceAsync(IMediaPipeImageSource* ImageSource);
	TFuture<bool> StartCameraAsync(int DeviceId = 0, int ResolutionX = 1280, int ResolutionY = 720, int FPS = 30);
	TFuture<void> StopAsync();
	
	//Blueprint Events
	UPROPERTY(Category="MediaPipe|Events", BlueprintAssignable)
	FOnVideoTextureCreated OnVideoTextureCreated;
	
	UPROPERTY(Category="MediaPipe|Events", BlueprintAssignable)
	FOnMediaPipeLifeCycle OnMediaPipeInitialized;

	UPROPERTY(Category="MediaPipe|Events", BlueprintAssignable)
	FOnMediaPipeLifeCycle OnMediaPipeStarted;

	UPROPERTY(Category="MediaPipe|Events", BlueprintAssignable)
	FOnMediaPipeLifeCycle OnMediaPipeStopped;

	UPROPERTY(Category="MediaPipe|Events", BlueprintAssignable)
	FOnMediaPipeLifeCycle OnMediaPipeThreadFault;

	//ImageSource
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe|Image Source")
	EResolutionLimits  SourceResolutionLimits = EResolutionLimits::P720_16_9;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MediaPipe|Image Source")
	bool  bSourceHorizontalFlip = false;
	
	const FMediaPipeHolisticOptions& GetAppliedOptions();

	FCriticalSection* GetStateCriticalSection() const;
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	 
 	virtual void HandlePoseLandmarks(TSharedPtr<TArray<FMediaPipeLandmark>> Landmarks) const;
	virtual void HandleLeftHandLandmarks(TSharedPtr<TArray<FMediaPipeLandmark>> Landmarks) const;
	virtual void HandleRightHandLandmarks(TSharedPtr<TArray<FMediaPipeLandmark>> Landmarks) const;
	virtual void HandleFaceLandmarks(TSharedPtr<TArray<FMediaPipeLandmark>> Landmarks) const;
	virtual void HandlePoseWorldLandmarks(TSharedPtr<TArray<FMediaPipeLandmark>> Landmarks) const;
	virtual void HandleFaceGeometry(TSharedPtr<FMediaPipeFaceMesh> FaceMesh) const;
	virtual void HandleFaceBlendShapes(TSharedPtr<FaceBlendShapes> BlendShapes) const;
	virtual void HandleImageResized(const FSizeInt& MPFrameSize);
	virtual void HandleMediaPipeFrameOut(TSharedRef<IMediaPipeOutFrame> InMat) const;

	void OnPlatformStart();
	void OnPlatformPause();
	void OnPlatformResume();
	void OnPlatformOrientationChanged(int Degrees);

	bool IsCustomConnector() const;
	virtual bool CanHandleMediaPipeCallback() const;
	virtual void AfterMediaPipeStarted();
	virtual void AfterMediaPipeStopped();
private:
	void RaiseMediaPipeInitialized();
	void ConfigureGraph(const FString& HolisticModelFile, MediaPipeGraphCnf& OutConfiguration);
	UPROPERTY(Transient)
	TObjectPtr<UWebcamImageSourceComponent> WebcamSource;
	void ClearWebcamImageSource();
	void WaitUntilWebcamClosed(int TimeoutSeconds = 5);
	FLandmarksOutEvent PoseWorldLandmarksEvent;
	FLandmarksOutEvent PoseLandmarksEvent;
	FLandmarksOutEvent LeftHandLandmarksEvent;
	FLandmarksOutEvent RightHandLandmarksEvent;
	FLandmarksOutEvent FaceLandmarksEvent;
	FClassificationsOutEvent FaceBlendShapesEvent;
	FaceGeometryOutEvent FaceGeometryEvent;
	bool bIsPipelineRunning = false;

	TUniquePtr<FDynamicTexture> VideoTexture;
	TWeakObjectPtr<UTexture2D> ImageSourceTexture;

	UPROPERTY()
	TScriptInterface<IMediaPipeImageSource> ScriptImageSource;
	IMediaPipeImageSource* NativeImageSource;

	FWebcamParams CurrentCamera;
	FHolisticPausedInfo HolisticPausedInfo;
	bool TrySetOpening();

	void OnWebcamOpenCompleted(bool bIsOpened);

	void OnWebcamFramePushed(TSharedRef<IMediaPipeTexture> Texture, int RotationDegrees);
	void OnImageSourceOpened(const FImageSourceInfo& ImageSourceInfo);
	bool StartInternal(IMediaPipeImageSource* InImageSource);
	bool StopInternal(long long SessionId, bool bWaitClose = false);
	
	bool DoStartCamera(int DeviceId = 0, int ResolutionX = 1280, int ResolutionY = 720, int FPS = 30);
	bool DoStartImageSource(IMediaPipeImageSource* ImageSource);
	
	virtual  void OnPipelineFault(long long SessionId);
	void SetCurrentImageSource(IMediaPipeImageSource* ImageSource);
	
	void SetupObservers();
	void ClearObservers() const;

	UFUNCTION()
	void RaiseTextureCreated(UTexture2D* Texture, int Width, int Height);

	FBeforeMediaPipeHolisticStart BeforeStartEvent;
	FOnMediaPipeHolisticStateChanged OnStartFailedEvent;
	FOnMediaPipeHolisticStateChanged OnStoppingEvent;
	FOnMediaPipeHolisticStateChanged OnStoppedEvent;
	FOnMediaPipeHolisticStateChanged OnStartedEvent;
	FVideoTextureCreatedEvent VideoTextureCreatedEvent; 
	
	friend FMediaPipeConnector;
	friend SMediaPipeCapturePanel;
	friend FStartImageSourceAction;
	friend StartHolisticComponentAsyncTask;
	friend UStopHolisticComponentAsyncTask;
private:
	
	void OnWebcamClosed();
	bool IsDisplayAnnotation() const;
	mutable FCriticalSection ClearWebcamCS;
	mutable FCriticalSection StateCS;
	mutable FCriticalSection PlatformEventCS;
	int64 CurrentSessionId = 0;
	bool bInitialized = false;
	bool bIsStopping = false;
	std::atomic<bool> bIsOpening = false;
	FMediaPipeHolisticOptions AppliedOptions;
	std::atomic<bool> bInitializationNotified = false;
	std::string HolisticModelFileUTF8;
	bool bCheckLandmarksCallbackErrorShown = false;
	void RemoveCustomConnector();
	IMediaPipeHolisticConnector& GetConnector() const;
	bool bUseCustomConnector = false;
	bool bIsNoneImage = false;
	TSharedPtr<IMediaPipeHolisticConnector> CustomConnector;
};


