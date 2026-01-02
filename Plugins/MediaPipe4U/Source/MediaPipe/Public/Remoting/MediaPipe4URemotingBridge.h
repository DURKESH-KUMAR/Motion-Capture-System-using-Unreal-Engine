// Copyright (c) 2025 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once

#include "CoreMinimal.h"
#include "IRemotingReceiver.h"
#include "OSCServer.h"

class MEDIAPIPE_API FMediaPipe4URemotingBridge : public TSharedFromThis<FMediaPipe4URemotingBridge>
{
public:
	inline static const FString OSCAddressPrefix = TEXT("/m4u");
	static FMediaPipe4URemotingBridge& Get();
	static TSharedRef<FMediaPipe4URemotingBridge>& GetShared();

	void StartIfAutoStartEnabled(bool bAsync = false); 
	bool Start();
	void Stop();
	bool IsRunning() const;
	int GetOSCPort() const;

	bool RegisterReceiver(const FString& MessagePath, const TSharedPtr<IRemotingReceiver>& Receiver, bool bReplaceExisted = false);
	bool UnregisterReceiver(const FString& MessagePath);
	static bool ValidateMessagePathFormat(const FString& MessagePath, bool bPrintError = true);
	
	FMediaPipe4URemotingBridge();
private:
	
	static FString NormalizeMessagePath(const FString& MessagePath);
	static void FlatBundleMessage(const FOSCBundle& BundleMessage, TArray<FOSCMessage>& OutMessages);
	FEvent* StartEvent = nullptr;
	void StopInternal();
	bool StartOSC();
	bool HasReceivers(ERemotingProtocols Protocol) const;
	void OnSOCMessageReceived(const FOSCMessage& Message, const FString& IPAddress, uint16 Port);
	void OnSOCBundleMessageReceived(const FOSCBundle& BundleMessage, const FString& IPAddress, uint16 Port);
	mutable FRWLock StartStopMutex;
	mutable FCriticalSection StartEventMutex;
	mutable FCriticalSection ReceiversMutex;
	UOSCServer* OSCServer = nullptr;
	TMap<FName, TSharedPtr<IRemotingReceiver>> Receivers;
	int OSCPort = 0;
};

