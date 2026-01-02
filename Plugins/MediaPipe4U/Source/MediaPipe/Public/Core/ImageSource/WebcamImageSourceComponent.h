// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "CoreMinimal.h"
#include "IWebcamProvider.h"
#include "MediaPipeImageSource.h"
#include "MediaPipeImageSourceComponent.h"
#include "WebcamImageSourceComponent.generated.h"


UCLASS(ClassGroup=(MediaPipe))
class MEDIAPIPE_API UWebcamImageSourceComponent : public UMediaPipeImageSourceComponent, public IImageSource
{
	GENERATED_BODY()

	DECLARE_EVENT_OneParam(UWebcamImageSourceComponent, FOnOpenCompleted, bool)
	DECLARE_EVENT_TwoParams(UWebcamImageSourceComponent, FOnFramePushed, TSharedRef<IMediaPipeTexture> Frame, int RotationDegrees)
	DECLARE_EVENT(UWebcamImageSourceComponent, FOnClosed)
public:
	// Sets default values for this component's properties
	UWebcamImageSourceComponent();
	virtual ~UWebcamImageSourceComponent() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Webcam")
	int DeviceId = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Webcam")
	int FrameWidth = 640;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Webcam")
	int FrameHeight = 480;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Webcam")
	float FrameRate = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Webcam")
	FName ProviderName = FName(TEXT(""));
	
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Webcam")
	// bool bEnableStreaming = true;

	UFUNCTION(BlueprintCallable, Category="Webcam")
	bool Open();
	
	UFUNCTION(BlueprintCallable, Category="Webcam")
	virtual void Close() override;

	UFUNCTION(BlueprintCallable, Category="Webcam")
	void PauseCapture();

	UFUNCTION(BlueprintCallable, Category="Webcam")
	void ResumeCapture();

	//Image Source interface
	virtual bool GetTexture(IMediaPipeTexture*& outTexture) override;
	virtual bool IsStatic() const override;
	virtual int GetWidth() const override;
	virtual int GetHeight() const override;
	virtual int GetWidthStep() const override;
	
	virtual MediaPipeImageFormat GetFormat() const override;

	

	//IMediaPipeImageSource interface
	virtual IImageSource* GetImageSource() override;

	virtual bool IsSupportHorizontalFlip() override;
	virtual bool IsSupportLimitResolution() override;
	virtual bool CorrectFrame(FFrameTransform& InOutTransform) override;

	virtual bool IsPushMode(); 
	
	FOnOpenCompleted& OnOpenCompletedEvent();
	FOnClosed& OnClosedEvent();
	FOnFramePushed& OnFramePushedEvent();
protected:
	virtual ELoopResult HandleInLoop() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void DestroyComponent(bool bPromoteChildren) override;
private:
	mutable FDelegateHandle OnOpenCompletedEventHandle;
	mutable FDelegateHandle OnClosedEventHandle;
	mutable FDelegateHandle OnFramePushedHandle;
	void UnbindProviderEvents() const;
	void OnCameraFramePushed(TSharedRef<IMediaPipeTexture> CameraFrame, int RotationDegrees); 
	void OnCameraOpenCompleted(bool bIsOpened, const FWebcamParams& CameraParams);
	void OnCameraClosed() const;
	FOnOpenCompleted OnOpenCompleted;
	FOnClosed OnClosed;
	FOnFramePushed OnFramePushed;
	FCriticalSection ProviderMutex;
	FName CurrentProvider = NAME_None;
	bool CreateWebcamProvider();
	bool ReadTexture(MediaPipeTexture* InOutTexture);
	std::atomic<bool> bIsRunning;
	TSharedPtr<IMediaPipeTexture> StagingText;
	bool bStopCapture = false;
	bool bStreamingMode = true;
	bool bFirstFrame = false;
	int64 ImageId = 0;
	TSharedPtr<IWebcamProvider> WebcamProvider;
};
