// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "CoreMinimal.h"

struct FVersion
{	
	bool IsInitialized() const { return Versions.Num() != 0; }

	FVersion(){}

	explicit FVersion(const FString& VersionString)
	{
		*this = VersionString;
	}

	void operator=(const FString& VersionString)
	{
		Versions.Reset();
		TArray<FString> Output;
		VersionString.ParseIntoArray(Output, TEXT("."));
		for (const FString& Item : Output)
		{
			Versions.Add(FCString::Atoi(*Item));
		}		
	}

	int32 Major() const
	{
		if(Versions.Num() >= 1)
		{
			return Versions[0];
		}
		return ZERO_VERSION;
	}

	int32 Minor() const
	{
		if(Versions.Num() >= 2)
		{
			return Versions[1];
		}
		return ZERO_VERSION;
	}

	int32 Patch() const
	{
		if(Versions.Num() >= 3)
		{
			return Versions[2];
		}
		return ZERO_VERSION;
	}

	bool operator<(const FVersion& rhs) const
	{
		TArray<int32>::SizeType LeftSize = Versions.Num();
		TArray<int32>::SizeType RightSize = rhs.Versions.Num();
		const TArray<int32>::SizeType Size = (LeftSize >= RightSize) ? RightSize : LeftSize;
		for(TArray<int32>::SizeType Index = 0; Index < Size; Index++)
		{
			const int32 LeftElement = Versions[Index];
			const int32 RightElement = rhs.Versions[Index];
			if(LeftElement < RightElement) return true;
			if(LeftElement > RightElement) return false;
		}
		return LeftSize < RightSize;
	}

	bool operator==(const FVersion& rhs) const
	{
		return !(*this < rhs) && !(rhs < *this); 
	}

	bool operator!=(const FVersion& rhs) const
	{
		return (*this < rhs) || (rhs < *this); 
	}

	FString ToString() const
	{
		return FString::JoinBy(Versions, TEXT("."), [](int32 Item)-> FString { return FString::FromInt(Item); });
	}

	
	TArray<int32> Versions;
	static constexpr int32 ZERO_VERSION = 0;
};