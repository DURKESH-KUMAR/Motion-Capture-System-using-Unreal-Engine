// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink	
#pragma once

#include "CoreMinimal.h"
#include "MediaPipeHolisticComponent.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "StopHolisticComponentAsyncTask.generated.h"

/**
 * 
 */
UCLASS(meta=(HideThen=true))
class MEDIAPIPEMOTION_API UStopHolisticComponentAsyncTask : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:
	UStopHolisticComponentAsyncTask(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category="MediaPipe|Async", meta=(BlueprintInternalUseOnly = "true"))
	static UStopHolisticComponentAsyncTask* StopAsync(UMediaPipeHolisticComponent* HolisticComponent);
 	
	virtual void Activate() override;

	// Called when start webcam completed (successfully or unsuccessfully)
	UPROPERTY(BlueprintAssignable, Category="MediaPipe")
	FOnAsyncTaskResult OnCompleted;
private:
	bool ValidateState() const;
	void PostResult();
	FWebcamParams RequestParam;
	TWeakObjectPtr<UMediaPipeHolisticComponent> Component;
};
