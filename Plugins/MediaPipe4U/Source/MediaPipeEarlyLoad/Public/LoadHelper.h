// Copyright (c) 2025 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once

#include "CoreMinimal.h"

class MEDIAPIPEEARLYLOAD_API LibraryLoadHelper
{
public:
	static FString GetThirdPartyBinariesFolder(const FString& PluginName, const FString& ThirdPartyFolderName, const FString& RuntimeFolder = "");
	static FString GetThirdPartyLibraryFile(const FString& PluginName, const FString& ThirdPartyFolderName,
	                                 const FString& ModuleName, const FString& RuntimeFolder = "");
private:
	LibraryLoadHelper() {}
};
