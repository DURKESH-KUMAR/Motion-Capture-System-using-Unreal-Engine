// Copyright (c) 2025 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "UObject/GCObject.h"
#include "Engine/Texture2D.h"

struct GSTREAMER_API FManagedTexture2D: public FGCObject
{
public:
	explicit FManagedTexture2D(UTexture2D* InTexture) : Texture(InTexture) {}
	FORCEINLINE UTexture2D* GetTexture() const { return Texture; }

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override
	{
		if (Texture)
		{
			Collector.AddReferencedObject(Texture);
		}
	}

	/** Optional: 给 GC 调试器显示名字 */
	virtual FString GetReferencerName() const override
	{
		return TEXT("GstManagedTexture2D");
	}
private:
	TObjectPtr<UTexture2D> Texture = nullptr;
};

class GSTREAMER_API FSharedTexture2D
{
public:
	explicit FSharedTexture2D(UTexture2D* InTexture2D); 
	FORCEINLINE FSharedTexture2D( SharedPointerInternals::FNullTag* = nullptr )
		: Texture(nullptr)
	{
	}

	UTexture2D* Get() const;
private:
	TSharedPtr<FManagedTexture2D> Texture;
public:
	FSharedTexture2D(const FSharedTexture2D& Other)
		: Texture(Other.Texture)
	{
	}

	FSharedTexture2D(FSharedTexture2D&& Other) noexcept
		: Texture(Other.Texture)
	{
		Other.Texture = nullptr;
	}

	FSharedTexture2D& operator=(const FSharedTexture2D& Other)
	{
		if (this == &Other)
			return *this;
		Texture = Other.Texture;
		return *this;
	}

	FSharedTexture2D& operator=(FSharedTexture2D&& Other) noexcept
	{
		if (this == &Other)
			return *this;
		Texture = MoveTemp(Other.Texture);
		return *this;
	}
	
	FORCEINLINE FSharedTexture2D& operator=( SharedPointerInternals::FNullTag* )
	{
		Texture.Reset();
		return *this;
	}

	[[nodiscard]] FORCEINLINE explicit operator bool() const
	{
		return Texture != nullptr && Texture->GetTexture() != nullptr;
	}
	
	[[nodiscard]] FORCEINLINE bool IsValid() const
	{
		return Texture != nullptr && Texture->GetTexture() != nullptr;
	}

	[[nodiscard]] FORCEINLINE UTexture2D& operator*() const
	{
		check( IsValid() );
		return *Texture.Get()->GetTexture();
	}

	[[nodiscard]] FORCEINLINE UTexture2D* operator->() const
	{
		check( IsValid() );
		return Texture.Get()->GetTexture();
	}
	
	FORCEINLINE void Reset()
	{
		Texture.Reset();
	}
};
