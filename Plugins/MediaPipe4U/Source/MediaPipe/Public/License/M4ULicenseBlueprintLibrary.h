// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "M4ULicenseBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintThreadSafe, ScriptName = "M4ULicenseLibrary"))
class MEDIAPIPE_API UM4ULicenseBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="MediaPipe|License", DisplayName="Get MediaPipe4U Device Id")
	static FString GetMediaPipe4UDeviceId();
	
    UFUNCTION(BlueprintCallable, Category="MediaPipe|License")
    static bool UpdateLicenseByContent(const FString& Content);

    UFUNCTION(BlueprintCallable, Category="MediaPipe|License")
    static bool UpdateLicenseByFile(const FString& FilePath);

private:
	static bool RefreshLicense();
};
