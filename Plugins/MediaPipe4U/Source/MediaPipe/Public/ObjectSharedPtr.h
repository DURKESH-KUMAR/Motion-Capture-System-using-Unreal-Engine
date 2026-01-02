// // Copyright (c) 2025 Anders Xiao. All rights reserved.
// // https://github.com/endink
// // Create: 2025-04-21

#pragma once
#include "CoreMinimal.h"
#include "UObject/GCObject.h"

template < typename TObject >
class TManagedObject final : FGCObject
{
public:
	FORCEINLINE explicit TManagedObject(TObject* InObject)
	{
		Object = InObject;
	}

	FORCEINLINE TObject* GetObject() { return Object; }

	FORCEINLINE virtual void AddReferencedObjects(FReferenceCollector& Collector) override
	{
		if (Object)
		{
			Collector.AddReferencedObject(Object);
		}
	}

	FORCEINLINE virtual FString GetReferencerName() const override
	{
		return Object ? FString::Printf(TEXT("ManagedObject:%s"), *Object->GetName()) : FString();
	}
private:
	TObjectPtr<TObject> Object = nullptr;
};

template< class UObjectType, ESPMode InMode = ESPMode::ThreadSafe > 
class TUObjectSharedPtr
{
	static constexpr ESPMode Mode = InMode;
public:
	FORCEINLINE TUObjectSharedPtr( SharedPointerInternals::FNullTag* = nullptr )
		: Obj(nullptr)
	{
	}
	FORCEINLINE explicit TUObjectSharedPtr(UObjectType* InUObject)
	{
		if (InUObject)
		{
			Obj = MakeShared<TManagedObject<UObjectType>, InMode>(InUObject); 
		}
	}
	
	[[nodiscard]] FORCEINLINE UObjectType* Get() const
	{
		return Obj.IsValid() ? Obj->GetObject() : nullptr;
	}

	FORCEINLINE void Reset()
	{
		Obj.Reset();
	}

private:
	TSharedPtr<TManagedObject<UObjectType>, InMode> Obj;
public:
	TUObjectSharedPtr(const TUObjectSharedPtr& Other)
		: Obj(Other.Obj)
	{
	}

	TUObjectSharedPtr(TUObjectSharedPtr&& Other) noexcept
		: Obj(Other.Obj)
	{
		Other.Obj = nullptr;
	}
	
	template <
		typename OtherType
		UE_REQUIRES(std::is_convertible_v<OtherType*, UObjectType*>)
	>
	FORCEINLINE TUObjectSharedPtr(const TSharedPtr< OtherType, Mode >& InSharedPtr )
		: Obj( InSharedPtr.Object )
	{
	}

	TUObjectSharedPtr& operator=(const TUObjectSharedPtr& Other)
	{
		if (this == &Other)
			return *this;
		Obj = Other.Obj;
		return *this;
	}

	TUObjectSharedPtr& operator=(TUObjectSharedPtr&& Other) noexcept
	{
		if (this == &Other)
			return *this;
		Obj = MoveTemp(Other.Obj);
		return *this;
	}

	FORCEINLINE TUObjectSharedPtr& operator=( SharedPointerInternals::FNullTag* )
	{
		Obj.Reset();
		return *this;
	}

	template <
		typename OtherType
		UE_REQUIRES(std::is_convertible_v<OtherType*, UObjectType*>)
	>
	FORCEINLINE TUObjectSharedPtr& operator=( SharedPointerInternals::TRawPtrProxy< OtherType > const& InRawPtrProxy )
	{
		*this = TSharedPtr<UObjectType, Mode>( InRawPtrProxy );
		return *this;
	}
	
	
	[[nodiscard]] FORCEINLINE operator bool() const
	{
		return Obj != nullptr && Obj->GetObject() != nullptr;
	}
	
	[[nodiscard]] FORCEINLINE bool IsValid() const
	{
		return Obj != nullptr && Obj->GetObject() != nullptr;
	}

	template <
		typename DummyObjectType = UObjectType
		UE_REQUIRES(UE_REQUIRES_EXPR(*(DummyObjectType*)nullptr)) // this construct means that operator* is only considered for overload resolution if T is dereferenceable
	>
	[[nodiscard]] FORCEINLINE DummyObjectType& operator*() const
	{
		check( IsValid() );
		return Obj.Get()->GetObject();
	}

	[[nodiscard]] FORCEINLINE UObjectType* operator->() const
	{
		check( IsValid() );
		return Obj.Get()->GetObject();
	}
	
	
	[[nodiscard]] FORCEINLINE int32 GetSharedReferenceCount() const
	{
		return Obj.GetSharedReferenceCount();
	}

};



