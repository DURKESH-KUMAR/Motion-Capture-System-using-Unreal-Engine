// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "UObject/ObjectMacros.h"
#include "MediaPipeControlRigElement.generated.h"

USTRUCT(BlueprintType)
struct MEDIAPIPEMOTION_API FMediaPipeControlRigElement
{
	GENERATED_BODY()
	
	FMediaPipeControlRigElement(const FMediaPipeControlRigElement& Other)
		: Name(Other.Name)
	{
	}

	FMediaPipeControlRigElement(FMediaPipeControlRigElement&& Other) noexcept
		: Name(MoveTemp(Other.Name))
	{
	}

	FMediaPipeControlRigElement& operator=(const FMediaPipeControlRigElement& Other)
	{
		if (this == &Other)
			return *this;
		Name = Other.Name;
		return *this;
	}

	FMediaPipeControlRigElement& operator=(FMediaPipeControlRigElement&& Other) noexcept
	{
		if (this == &Other)
			return *this;
		Name = MoveTemp(Other.Name);
		return *this;
	}

	FMediaPipeControlRigElement(){}
	FMediaPipeControlRigElement(const FName& InName): Name(InName) {}
	FMediaPipeControlRigElement(const FString& InName): Name(InName) {}
	FMediaPipeControlRigElement(const TCHAR* InName): Name(InName) {} 

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="General")
	FName Name = NAME_None;
	static const FMediaPipeControlRigElement None;


	inline bool IsValid() const { return Name != NAME_None && Name.IsValid(); }

	operator FName() const
	{
		return Name;
	}
};

