// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <functional>

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/Object.h"
#include "ZipBlueprintLibrary.generated.h"


DECLARE_DYNAMIC_DELEGATE_OneParam(FOnUnzipProgress, float, Percent);
DECLARE_DELEGATE_OneParam(FOnUnzipProgressDelegate, float);

class ZipEntry;

/**
 * 
 */
UCLASS(meta=(BlueprintThreadSafe, ScriptName = "ZipBlueprintLibrary"))
class MEDIAPIPE_API UZipBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static bool ExistPath(const FString& ZipFile, const FString& RelativePath);

	UFUNCTION(BlueprintCallable, Category="Unzip")
	static bool UnzipFileToFolder(const FString& ZipFile,
		const FString& SaveFolder,
		const FOnUnzipProgress& OnWritten,
		bool bCreateFolderIfNotExisted = true);


	static bool UnzipFileToFolder(const FString& ZipFile,
		const FString& SaveFolder,
		const FOnUnzipProgressDelegate& OnWritten,
		bool bCreateFolderIfNotExisted = true);

private:
	static void OnProgressCallback(float Percent, const FOnUnzipProgress OnUnzipProgress);
	static bool GetUncompressedSizeInBytes(const FString& ZipFile, unsigned long& TotalBytes);
	static bool ForEachFile(const FString& ZipFile, std::function<bool(ZipEntry& Entry)> Action);
};

