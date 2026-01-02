// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "HAL/Platform.h"


class MEDIAPIPE_API FScopeCudaDriverLibrary
{
public:
	FScopeCudaDriverLibrary();
	~FScopeCudaDriverLibrary();
	bool cuDriverGetVersion(int& MajorVerMax, int& MinorVerMax) const;
	void* GetDllExport(const TCHAR* FunName) const;
	bool IsValid() const;
private:
	void* DriverLibrary;
};
