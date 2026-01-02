// Copyright (c) 2025 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "PlatformUIBlueprintLibrary.generated.h"


UCLASS(meta=(ScriptName="PlatformUILibrary"))
class MEDIAPIPE_API UPlatformUIBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	/**
	 * 
	 * @param SelectedFile Opened files.
	 * @param FilterNames File type name separated by comma (e.g., Image Files,Video Files).
	 * @param FilterExtensions  Filter file extensions, group separated by comma, group element separated by whitespace  (e.g., *. jpg *.jpeg *.png,*.mp4 *.avi)
	 * @param Title Dialog title.
	 * @param DefaultPath Default folder path.
	 * @return If the user canceled the operation, return false.
	 * 
	 * @example
	 *	- OpenSingleFile(File, "Image Files,Video Files", "*. jpg *.jpeg *.png,*.mp4 *.avi");
	 *	- OpenSingleFile(File, "Image Files,Video Files", "*. jpg *.jpeg *.png,*.mp4 *.avi", "OpenMedia");
	 *	- OpenSingleFile(File, "All Files", "*.*");
	 */
	UFUNCTION(BlueprintCallable, Category = "PlatformUI", meta=(ReturnDisplayName="Selected"))
	static bool OpenSingleFile(
		FString& SelectedFile,
		const FString& FilterNames = "All Files",
		const FString& FilterExtensions = "*.*",
		const FString& Title = "Select a file",
		const FString& DefaultPath = "");


	/**
	 * 
	 * @param SelectedFiles Opened files.
	 * @param FilterNames File type name separated by comma (e.g., Image Files,Video Files).
	 * @param FilterExtensions  Filter file extensions, group separated by comma, group element separated by whitespace  (e.g., *. jpg *.jpeg *.png,*.mp4 *.avi)
	 * @param Title Dialog title.
	 * @param DefaultPath Default folder path.
	 * @return If the user canceled the operation, return false.
	 * 
	 * @example
	 *	- OpenMultiFiles(Files, "Image Files,Video Files", "*. jpg *.jpeg *.png,*.mp4 *.avi");
	 *	- OpenMultiFiles(Files, "Image Files,Video Files", "*. jpg *.jpeg *.png,*.mp4 *.avi", "OpenMedia");
	 *	- OpenMultiFiles(Files, "All Files", "*.*");
	 */
	UFUNCTION(BlueprintCallable, Category = "PlatformUI", meta=(ReturnDisplayName="Selected"))
	static bool OpenMultiFiles(
		TArray<FString>& SelectedFiles,
		const FString& FilterNames = "All Files",
		const FString& FilterExtensions = "*.*",
		const FString& Title = "Select files",
		const FString& DefaultPath = "");

	/**
	 * 
	 * @param SelectedFile Opened file for save.
	 * @param FilterNames File type name separated by comma (e.g., Image Files,Video Files).
	 * @param FilterExtensions  Filter file extensions, group separated by comma, group element separated by whitespace  (e.g., *. jpg *.jpeg *.png,*.mp4 *.avi)
	 * @param Title Dialog title.
	 * @param DefaultPath Default folder path.
	 * @param bOverwriteIfExisted If true, force overwrite and disable the confirmation dialog else show confirmation dialog.
	 * @return If the user canceled the operation, return false.
	 * 
	 * @example
	 *	- OpenMultiFiles(Files, "Image Files,Video Files", "*. jpg *.jpeg *.png,*.mp4 *.avi");
	 *	- OpenMultiFiles(Files, "Image Files,Video Files", "*. jpg *.jpeg *.png,*.mp4 *.avi", "OpenMedia");
	 *	- OpenMultiFiles(Files, "All Files", "*.*");
	 */
	UFUNCTION(BlueprintCallable, Category = "PlatformUI", meta=(ReturnDisplayName="Selected"))
	static bool OpenSaveFile(
		FString& SelectedFile,
		const FString& FilterNames = "All Files",
		const FString& FilterExtensions = "*.*",
		const FString& Title = "Select a file",
		const FString& DefaultPath = "",
		const bool bOverwriteIfExisted = false);

	
	/**
	 * 
	 * @param SelectedFolder Selected folder.
	 * @param Title Dialog title.
	 * @param DefaultPath Default folder path.
	 * @return If the user canceled the operation, return false.
	 */
	UFUNCTION(BlueprintCallable, Category = "PlatformUI", meta=(ReturnDisplayName="Selected"))
	static bool OpenFolder(
		FString& SelectedFolder,
		const FString& Title = "Select a file",
		const FString& DefaultPath = "");
	
	/**
	 * 
	 * @param SelectedFile Opened files.
	 * @param FilterNames Filter name (e.g., images files, video files).
	 * @param FilterExtensions  Filter file extensions separated by spaces (e.g., *. jpg *.jpeg *.png)
	 * @param Title Dialog title.
	 * @param DefaultPath Default folder path.
	 * @return If the user canceled the operation, return false.
	 */
	static bool OpenSingleFile(
		FString& SelectedFile,
		const TArray<FString>& FilterNames,
		const TArray<FString>& FilterExtensions,
		const FString& Title = "Select a file",
		const FString& DefaultPath = "");

	/**
	 * 
	 * @param SelectedFiles Opened files.
	 * @param FilterNames Filter name (e.g., images files, video files).
	 * @param FilterExtensions  Filter file extensions separated by spaces (e.g., *. jpg *.jpeg *.png)
	 * @param Title Dialog title.
	 * @param DefaultPath Default folder path.
	 * @return If the user canceled the operation, return false.
	 */
	static bool OpenMultiFiles(
		TArray<FString>& SelectedFiles,
		const TArray<FString>& FilterNames,
		const TArray<FString>& FilterExtensions,
		const FString& Title = "Select files",
		const FString& DefaultPath = "");

	/**
	 * 
	 * @param SelectedFile Selected file to save.
	 * @param FilterNames Filter name (e.g., images files, video files).
	 * @param FilterExtensions  Filter file extensions separated by spaces (e.g., *. jpg *.jpeg *.png)
	 * @param Title Dialog title.
	 * @param DefaultPath Default folder path.
	 * @param bOverwriteIfExisted If true, force overwrite and disable the confirmation dialog else show confirmation dialog.
	 * @return If the user canceled the operation, return false.
	 */
	static bool OpenSaveFile(
		FString& SelectedFile,
		const TArray<FString>& FilterNames,
		const TArray<FString>& FilterExtensions,
		const FString& Title = "Select a file",
		const FString& DefaultPath = "",
		const bool bOverwriteIfExisted = false);

};
