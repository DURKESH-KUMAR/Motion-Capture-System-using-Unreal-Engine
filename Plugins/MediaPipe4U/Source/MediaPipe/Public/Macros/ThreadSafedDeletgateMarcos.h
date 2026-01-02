// // Copyright (c) 2025 Anders Xiao. All rights reserved.
// // https://github.com/endink
// // Create: 2025-04-29

// ReSharper disable CppUE4CodingStandardNamingViolationWarning
#pragma once

#include "ThreadSafedDeletgate.h"


#define FUNC_DECLARE_THREAD_SAFE_EVENT( OwningType, EventName, ... ) \
class EventName: public TThreadSafeMulticastDelegateBase<__VA_ARGS__> \
{ \
	friend class OwningType; \
};

#define DECLARE_THREAD_SAFE_EVENT( OwningType, EventName ) FUNC_DECLARE_THREAD_SAFE_EVENT( OwningType, EventName )
#define DECLARE_THREAD_SAFE_EVENT_OneParam( OwningType, EventName, Param1Type ) FUNC_DECLARE_THREAD_SAFE_EVENT( OwningType, EventName, Param1Type )
#define DECLARE_THREAD_SAFE_EVENT_TwoParams( OwningType, EventName, Param1Type, Param2Type ) FUNC_DECLARE_THREAD_SAFE_EVENT( OwningType, EventName, Param1Type, Param2Type)
#define DECLARE_THREAD_SAFE_EVENT_ThreeParams( OwningType, EventName, Param1Type, Param2Type, Param3Type ) FUNC_DECLARE_THREAD_SAFE_EVENT( OwningType, EventName, Param1Type, Param2Type, Param2Type)
