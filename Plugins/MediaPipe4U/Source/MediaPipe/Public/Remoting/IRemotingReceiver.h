// // Copyright (c) 2025 Anders Xiao. All rights reserved.
// // https://github.com/endink
// // Create: 2025-04-07

#pragma once
#include "CoreMinimal.h"
#include "OSCMessage.h"
#include "RemotingProtocol.h"

class IRemotingReceiver
{
public:
	virtual ~IRemotingReceiver() = default;
	virtual bool IsEnabled(ERemotingProtocols Protocol) const = 0;
	virtual void OnOSCMessage(const FOSCMessage& Message) = 0;
};
