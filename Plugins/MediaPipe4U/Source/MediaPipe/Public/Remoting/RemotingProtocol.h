// // Copyright (c) 2025 Anders Xiao. All rights reserved.
// // https://github.com/endink
// // Create: 2025-04-07

#pragma once
#include "CoreMinimal.h"
#include "RemotingProtocol.generated.h"

UENUM(BlueprintType, Meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class ERemotingProtocols : uint8 {
	None    = 0,
	OSC = 1 << 0,  
	// WebSocket = 1 << 1,
	// HttpStream = 1 << 2,  
};

ENUM_CLASS_FLAGS(ERemotingProtocols);