// // Copyright (c) 2025 Anders Xiao. All rights reserved.
// // https://github.com/endink
// // Create: 2025-04-29

#pragma once
#include "CoreMinimal.h"
#include "Misc/ScopeRWLock.h"


template <typename... ParamTypes>
class TThreadSafeMulticastDelegateBase
{
	using FInnerEvent = TMulticastDelegate<void(ParamTypes...), FNotThreadSafeNotCheckedDelegateUserPolicy>;
	using FDelegate = TDelegate<void(ParamTypes...)>;
public:
	virtual ~TThreadSafeMulticastDelegateBase() = default;

	FDelegateHandle Add(FDelegate&& InNewDelegate)
	{
		FWriteScopeLock Lock(Mutex);
		return Event.Add(MoveTemp(InNewDelegate));
	}

	/**
	 * Adds a delegate instance to this multicast delegate's invocation list.
	 *
	 * @param InNewDelegate The delegate to add.
	 */
	FDelegateHandle Add(const FDelegate& InNewDelegate)
	{
		FWriteScopeLock Lock(Mutex);
		return Event.Add(InNewDelegate);
	}

	/**
	 * Adds a raw C++ pointer global function delegate
	 *
	 * @param	InFunc	Function pointer
	 */
	template <typename... VarTypes>
	inline FDelegateHandle AddStatic(typename TBaseStaticDelegateInstance<void (ParamTypes...), std::decay_t<VarTypes>...>::FFuncPtr InFunc, VarTypes&&... Vars)
	{
		FWriteScopeLock Lock(Mutex);
		return Event.AddStatic(InFunc, Forward<VarTypes>(Vars)...);
	}

	/**
	 * Adds a C++ lambda delegate
	 * technically this works for any functor types, but lambdas are the primary use case
	 *
	 * @param	InFunctor	Functor (e.g. Lambda)
	 */
	template<typename FunctorType, typename... VarTypes>
	inline FDelegateHandle AddLambda(FunctorType&& InFunctor, VarTypes&&... Vars)
	{
		FWriteScopeLock Lock(Mutex);
		return Event.AddLambda(InFunctor, Forward<VarTypes>(Vars)...);
	}

	/**
	 * Adds a weak shared pointer C++ lambda delegate
	 * technically this works for any functor types, but lambdas are the primary use case
	 *
	 * @param	InUserObject	User object to bind to
	 * @param	InFunctor		Functor (e.g. Lambda)
	 */
	template <typename UserClass, typename FunctorType, typename... VarTypes>
	inline FDelegateHandle AddSPLambda(const UserClass* InUserObject, FunctorType&& InFunctor, VarTypes&&... Vars)
	{
		FWriteScopeLock Lock(Mutex);
		return Event.AddSPLambda(InUserObject, InFunctor, Forward<VarTypes>(Vars)...);
	}

	/**
	 * Adds a weak object C++ lambda delegate
	 * technically this works for any functor types, but lambdas are the primary use case
	 *
	 * @param	InUserObject	User object to bind to
	 * @param	InFunctor		Functor (e.g. Lambda)
	 */
	template<typename UserClass, typename FunctorType, typename... VarTypes>
	inline FDelegateHandle AddWeakLambda(UserClass* InUserObject, FunctorType&& InFunctor, VarTypes&&... Vars)
	{
		FWriteScopeLock Lock(Mutex);
		return Event.AddWeakLambda(InUserObject, InFunctor, Forward<VarTypes>(Vars)...);
	}

	/**
	 * Adds a raw C++ pointer delegate.
	 *
	 * Raw pointer doesn't use any sort of reference, so may be unsafe to call if the object was
	 * deleted out from underneath your delegate. Be careful when calling Execute()!
	 *
	 * @param	InUserObject	User object to bind to
	 * @param	InFunc			Class method function address
	 */
	template <typename UserClass, typename... VarTypes>
	inline FDelegateHandle AddRaw(UserClass* InUserObject, typename TMemFunPtrType<false, UserClass, void (ParamTypes..., std::decay_t<VarTypes>...)>::Type InFunc, VarTypes&&... Vars)
	{
		static_assert(!TIsConst<UserClass>::Value, "Attempting to bind a delegate with a const object pointer and non-const member function.");
		
		FWriteScopeLock Lock(Mutex);
		return Event.AddRaw(InUserObject, InFunc, Forward<VarTypes>(Vars)...);
	}
	template <typename UserClass, typename... VarTypes>
	inline FDelegateHandle AddRaw(const UserClass* InUserObject, typename TMemFunPtrType<true, UserClass, void (ParamTypes..., std::decay_t<VarTypes>...)>::Type InFunc, VarTypes&&... Vars)
	{
		FWriteScopeLock Lock(Mutex);
		return Event.AddRaw(InUserObject, InFunc, Forward<VarTypes>(Vars)...);
	}

	/**
	 * Adds a shared pointer-based member function delegate.
	 *
	 * Shared pointer delegates keep a weak reference to your object.
	 *
	 * @param	InUserObjectRef	User object to bind to
	 * @param	InFunc			Class method function address
	 */
	template <typename UserClass, ESPMode Mode, typename... VarTypes>
	inline FDelegateHandle AddSP(const TSharedRef<UserClass, Mode>& InUserObjectRef, typename TMemFunPtrType<false, UserClass, void (ParamTypes..., std::decay_t<VarTypes>...)>::Type InFunc, VarTypes&&... Vars)
	{
		static_assert(!TIsConst<UserClass>::Value, "Attempting to bind a delegate with a const object pointer and non-const member function.");

		FWriteScopeLock Lock(Mutex);
		return Event.AddSP(InUserObjectRef, InFunc, Forward<VarTypes>(Vars)...);
	}
	template <typename UserClass, ESPMode Mode, typename... VarTypes>
	inline FDelegateHandle AddSP(const TSharedRef<UserClass, Mode>& InUserObjectRef, typename TMemFunPtrType<true, UserClass, void (ParamTypes..., std::decay_t<VarTypes>...)>::Type InFunc, VarTypes&&... Vars)
	{
		FWriteScopeLock Lock(Mutex);
		return Event.AddSP(InUserObjectRef, InFunc, Forward<VarTypes>(Vars)...);
	}

	/**
	 * Adds a shared pointer-based member function delegate.
	 *
	 * Shared pointer delegates keep a weak reference to your object.
	 *
	 * @param	InUserObject	User object to bind to
	 * @param	InFunc			Class method function address
	 */
	template <typename UserClass, typename... VarTypes>
	inline FDelegateHandle AddSP(UserClass* InUserObject, typename TMemFunPtrType<false, UserClass, void (ParamTypes..., std::decay_t<VarTypes>...)>::Type InFunc, VarTypes&&... Vars)
	{
		static_assert(!TIsConst<UserClass>::Value, "Attempting to bind a delegate with a const object pointer and non-const member function.");

		FWriteScopeLock Lock(Mutex);
		return Event.AddSP(InUserObject, InFunc, Forward<VarTypes>(Vars)...);
	}
	template <typename UserClass, typename... VarTypes>
	inline FDelegateHandle AddSP(const UserClass* InUserObject, typename TMemFunPtrType<true, UserClass, void (ParamTypes..., std::decay_t<VarTypes>...)>::Type InFunc, VarTypes&&... Vars)
	{
		FWriteScopeLock Lock(Mutex);
		return Event.AddSP(InUserObject, InFunc, Forward<VarTypes>(Vars)...);
	}

	/**
	 * Adds a shared pointer-based (thread-safe) member function delegate.  Shared pointer delegates keep a weak reference to your object.
	 *
	 * @param	InUserObjectRef	User object to bind to
	 * @param	InFunc			Class method function address
	 *
	 * Note: This function is redundant, but is retained for backwards compatibility.  AddSP() works in both thread-safe and not-thread-safe modes and should be preferred.
	 */
	template <typename UserClass, typename... VarTypes>
	inline FDelegateHandle AddThreadSafeSP(const TSharedRef<UserClass, ESPMode::ThreadSafe>& InUserObjectRef, typename TMemFunPtrType<false, UserClass, void (ParamTypes..., std::decay_t<VarTypes>...)>::Type InFunc, VarTypes&&... Vars)
	{
		static_assert(!TIsConst<UserClass>::Value, "Attempting to bind a delegate with a const object pointer and non-const member function.");

		FWriteScopeLock Lock(Mutex);
		return Event.AddThreadSafeSP(InUserObjectRef, InFunc, Forward<VarTypes>(Vars)...);
	}
	
	template <typename UserClass, typename... VarTypes>
	inline FDelegateHandle AddThreadSafeSP(const TSharedRef<UserClass, ESPMode::ThreadSafe>& InUserObjectRef, typename TMemFunPtrType<true, UserClass, void (ParamTypes..., std::decay_t<VarTypes>...)>::Type InFunc, VarTypes&&... Vars)
	{
		FWriteScopeLock Lock(Mutex);
		return Event.AddThreadSafeSP(InUserObjectRef, InFunc, Forward<VarTypes>(Vars)...);
	}

	/**
	 * Adds a shared pointer-based (thread-safe) member function delegate.
	 *
	 * Shared pointer delegates keep a weak reference to your object.
	 *
	 * @param	InUserObject	User object to bind to
	 * @param	InFunc			Class method function address
	 *
	 * Note: This function is redundant, but is retained for backwards compatibility.  AddSP() works in both thread-safe and not-thread-safe modes and should be preferred.
	 */
	template <typename UserClass, typename... VarTypes>
	inline FDelegateHandle AddThreadSafeSP(UserClass* InUserObject, typename TMemFunPtrType<false, UserClass, void (ParamTypes..., std::decay_t<VarTypes>...)>::Type InFunc, VarTypes&&... Vars)
	{
		static_assert(!TIsConst<UserClass>::Value, "Attempting to bind a delegate with a const object pointer and non-const member function.");

		FWriteScopeLock Lock(Mutex);
		return Event.AddThreadSafeSP(InUserObject, InFunc, Forward<VarTypes>(Vars)...);
	}
	template <typename UserClass, typename... VarTypes>
	inline FDelegateHandle AddThreadSafeSP(const UserClass* InUserObject, typename TMemFunPtrType<true, UserClass, void (ParamTypes..., std::decay_t<VarTypes>...)>::Type InFunc, VarTypes&&... Vars)
	{
		FWriteScopeLock Lock(Mutex);
		return Event.AddThreadSafeSP(InUserObject, InFunc, Forward<VarTypes>(Vars)...);
	}

	/**
	 * Adds a UFunction-based member function delegate.
	 *
	 * UFunction delegates keep a weak reference to your object.
	 *
	 * @param	InUserObject	User object to bind to
	 * @param	InFunctionName			Class method function address
	 */
	template <typename UObjectTemplate, typename... VarTypes>
	inline FDelegateHandle AddUFunction(UObjectTemplate* InUserObject, const FName& InFunctionName, VarTypes&&... Vars)
	{
		FWriteScopeLock Lock(Mutex);
		return Event.AddUFunction(InUserObject, InFunctionName, Forward<VarTypes>(Vars)...);
	}
	template <typename UObjectTemplate, typename... VarTypes>
	inline FDelegateHandle AddUFunction(TObjectPtr<UObjectTemplate> InUserObject, const FName& InFunctionName, VarTypes&&... Vars)
	{
		FWriteScopeLock Lock(Mutex);
		return Event.AddUFunction(InUserObject, InFunctionName, Forward<VarTypes>(Vars)...);
	}

	/**
	 * Adds a UObject-based member function delegate.
	 *
	 * UObject delegates keep a weak reference to your object.
	 *
	 * @param	InUserObject	User object to bind to
	 * @param	InFunc			Class method function address
	 */
	template <typename UserClass, typename... VarTypes>
	inline FDelegateHandle AddUObject(UserClass* InUserObject, typename TMemFunPtrType<false, UserClass, void (ParamTypes..., std::decay_t<VarTypes>...)>::Type InFunc, VarTypes&&... Vars)
	{
		static_assert(!TIsConst<UserClass>::Value, "Attempting to bind a delegate with a const object pointer and non-const member function.");

		FWriteScopeLock Lock(Mutex);
		return Event.AddUObject(InUserObject, InFunc, Forward<VarTypes>(Vars)...);
	}
	
	template <typename UserClass, typename... VarTypes>
	inline FDelegateHandle AddUObject(const UserClass* InUserObject, typename TMemFunPtrType<true, UserClass, void (ParamTypes..., std::decay_t<VarTypes>...)>::Type InFunc, VarTypes&&... Vars)
	{
		FWriteScopeLock Lock(Mutex);
		return Event.AddUObject(InUserObject, InFunc, Forward<VarTypes>(Vars)...);
	}
	
	template <typename UserClass, typename... VarTypes>
	inline FDelegateHandle AddUObject(TObjectPtr<UserClass> InUserObject, typename TMemFunPtrType<false, UserClass, void (ParamTypes..., std::decay_t<VarTypes>...)>::Type InFunc, VarTypes&&... Vars)
	{
		static_assert(!TIsConst<UserClass>::Value, "Attempting to bind a delegate with a const object pointer and non-const member function.");
		FWriteScopeLock Lock(Mutex);
		return Event.AddUObject(InUserObject, InFunc, Forward<VarTypes>(Vars)...);
	}
	template <typename UserClass, typename... VarTypes>
	inline FDelegateHandle AddUObject(TObjectPtr<UserClass> InUserObject, typename TMemFunPtrType<true, UserClass, void (ParamTypes..., std::decay_t<VarTypes>...)>::Type InFunc, VarTypes&&... Vars)
	{
		FWriteScopeLock Lock(Mutex);
		return Event.AddUObject(InUserObject, InFunc, Forward<VarTypes>(Vars)...);
	}
	
	inline bool Remove( FDelegateHandle Handle )
	{
		if (!Handle.IsValid())
		{
			return false;
		}
		if (bInCallback)
		{
			RemoveInCallback.Add(Handle);
			return true;
		}
		FWriteScopeLock Lock(Mutex);
		return Event.Remove(Handle);
	}
	
	inline bool IsBoundToObject( void const* InUserObject ) const
	{
		if (!bInCallback)
		{
			FReadScopeLock Lock(Mutex);
			return Event.IsBoundToObject(InUserObject);
		}
		return Event.IsBoundToObject(InUserObject);
	}

	inline void RemoveAll( void const* InUserObject , int32* RemoveCount = nullptr)
	{
		if (InUserObject == nullptr)
		{
			return;
		}
		if (bInCallback)
		{
			bool isBound =  Event.IsBoundToObject(InUserObject);
			if (isBound)
			{
				RemoveAllInCallback.Add(InUserObject);
			}
			if (RemoveCount != nullptr)
			{
				*RemoveCount = isBound ? 1 : 0;
			}
			return;
		}
		FWriteScopeLock Lock(Mutex);
		if (Event.IsBoundToObject(InUserObject))
		{
			const int32 c = Event.RemoveAll(InUserObject);
			if (RemoveCount != nullptr)
			{
				*RemoveCount = c;
			}
		}
		else
		{
			if (RemoveCount != nullptr)
			{
				*RemoveCount = 0;
			}
		}
	}
	
protected:

	inline void BroadcastIfBoundNoCheck(ParamTypes... Params) const
	{
		if (!bInCallback)
		{
			FReadScopeLock Lock(Mutex);
			if (Event.IsBound())
			{
				bInCallback = true;
				Event.Broadcast(Params...);
				bInCallback = false;
			}
		}
	}

	inline bool BroadcastIfBound(ParamTypes... Params) const
	{
		if (!bInCallback)
		{
			FReadScopeLock Lock(Mutex);
			if (Event.IsBound())
			{
				bInCallback = true;
				Event.Broadcast(Params...);
				bInCallback = false;
				return true;
			}
		}
		return false;
	}

	inline bool IsBound() const
	{
		if (!bInCallback)
		{
			Mutex.ReadLock();
		}
		bool ok = Event.IsBound();
		if (!bInCallback)
		{
			Mutex.ReadUnlock();
		}
		return ok;
	}

	inline void Clear()
	{
		if (bInCallback)
		{
			bClearInCallback = true;
			return;
		}
		FWriteScopeLock Lock(Mutex);
		Event.Clear();
	}
	
	inline void Broadcast(ParamTypes... Params) const
	{
		{
			FReadScopeLock Lock(Mutex);
			bInCallback = true;
			Event.Broadcast(Params...);
			bInCallback = false;
		}
		if (!RemoveInCallback.IsEmpty() || !RemoveAllInCallback.IsEmpty() || bClearInCallback)
		{
			FWriteScopeLock Lock(Mutex);
			if (bClearInCallback)
			{
				Event.Clear();
			}
			else
			{
				for (auto& o : RemoveAllInCallback)
				{
					Event.RemoveAll(o);
				}
				for (auto& h : RemoveInCallback)
				{
					Event.Remove(h);
				}
			}
			bClearInCallback = false;
			RemoveInCallback.Reset();
			RemoveAllInCallback.Reset();
		}
	}

private:
	mutable FRWLock Mutex;
	mutable FInnerEvent Event;
	mutable bool bInCallback = false;
	mutable TArray<FDelegateHandle> RemoveInCallback;
	mutable TArray<void const*> RemoveAllInCallback;
	mutable bool bClearInCallback = false;
};

