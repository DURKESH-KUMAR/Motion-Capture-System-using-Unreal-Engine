// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "Containers/UnrealString.h"

class MEDIAPIPE_API FPlatformFileSystem
{
public:
	static const TCHAR* GetProjectBinariesFolder();
	static FString Get3rdModuleDataFolder(const FString& PluginName, const FString& ModuleName);
	static bool ReadFileToString(FString& Result, const FString& FilePath);
	static bool ReadFileToBytes(TArray<uint8>& Result, const FString& FilePath);
	static bool IsFileExisted(const FString& FilePath);
};
