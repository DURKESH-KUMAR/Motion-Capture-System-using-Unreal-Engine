// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "CoreMinimal.h"
#include "HAL/PlatformProcess.h"

class MEDIAPIPE_API FThirdPartyLibLoader
{
public:
	FThirdPartyLibLoader();
	FThirdPartyLibLoader(const FThirdPartyLibLoader& Other);
	FThirdPartyLibLoader(FThirdPartyLibLoader&& Other) noexcept;
	FThirdPartyLibLoader(const TCHAR* LibFileNameWithoutExtensions, const TCHAR* ThirdPartyModuleName, const FString& PluginName = "MediaPipe4U");


	template<typename FuncPtr>
	inline FuncPtr GetDLLExportFunction(const TCHAR* ProcName) const
	{
		if(LibHandle)
		{
			return (FuncPtr)FPlatformProcess::GetDllExport(LibHandle, ProcName);
		}
		return nullptr;
	}
	
	void FreeHandle();
	FString FileName{};
	FString FullFilePath{};
	FString BinariesDir{};

	void* LibHandle = nullptr;
	FString Name;
	

	FThirdPartyLibLoader& operator=(const FThirdPartyLibLoader& Other);
	FThirdPartyLibLoader& operator=(FThirdPartyLibLoader&& Other) noexcept;

private:
	bool LoadLibraryInternal(const FString& InFileName);
};
