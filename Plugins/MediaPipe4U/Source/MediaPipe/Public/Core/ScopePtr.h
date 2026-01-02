// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "CoreMinimal.h"

DECLARE_DELEGATE_OneParam(FScopeDeletion, void*)

class MEDIAPIPE_API FScopePtr
{
public:
	FScopePtr(void* Ptr, const FScopeDeletion& InDeletion)
	{
		ObjectPtr = Ptr;
		Deletion = InDeletion;
	}
	~FScopePtr()
	{
		if(ObjectPtr != nullptr)
		{
			Deletion.ExecuteIfBound(ObjectPtr);
		}
	}
private:
	void* ObjectPtr;
	FScopeDeletion Deletion;
};
