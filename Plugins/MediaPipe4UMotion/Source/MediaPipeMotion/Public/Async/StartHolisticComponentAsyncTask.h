// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "MediaPipeHolisticComponent.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "StartHolisticComponentAsyncTask.generated.h"

UCLASS(meta=(HideThen=true))
class MEDIAPIPEMOTION_API UStartHolisticComponentAsyncTask : public UBlueprintAsyncActionBase
{
	enum class EStartType
	{
		Camera,
		ImageSource,
	};
	GENERATED_BODY()

public:
	UStartHolisticComponentAsyncTask(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category="MediaPipe|Async", DisplayName="Start Image Source Async", meta=(BlueprintInternalUseOnly = "true"))
	static UStartHolisticComponentAsyncTask* StartImageSourceAsync(UMediaPipeHolisticComponent* HolisticComponent, const TScriptInterface<IMediaPipeImageSource>& ImageSource);

	UFUNCTION(BlueprintCallable, Category="MediaPipe|Async", DisplayName="Start Camera Async", meta=(BlueprintInternalUseOnly = "true"))
	static UStartHolisticComponentAsyncTask* StartCameraAsync(UMediaPipeHolisticComponent* HolisticComponent, int DeviceId = 0, int ResolutionX = 1280, int ResolutionY = 720, int FPS = 30);
	
	virtual void Activate() override;  

	// Called when start image source completed successfully
	UPROPERTY(BlueprintAssignable, Category="MediaPipe")
	FOnAsyncTaskResult OnSuccess;

	// Called when start image source completed unsuccessfully
	UPROPERTY(BlueprintAssignable, Category="MediaPipe")
	FOnAsyncTaskResult OnFailure;

	// Called when start image source completed (successfully or unsuccessfully)
	UPROPERTY(BlueprintAssignable, Category="MediaPipe")
	FOnAsyncTaskResult OnCompleted;
private:
	bool ValidateState() const;
	void PostResult(bool Success);
	TWeakObjectPtr<UMediaPipeHolisticComponent>Component;
	TWeakObjectPtr<UObject> Source;
	FWebcamParams RequestParam;
	EStartType Target = EStartType::Camera;
};
