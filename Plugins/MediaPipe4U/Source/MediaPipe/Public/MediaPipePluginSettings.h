// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PluginEdition.h"
#include "Remoting/RemotingProtocol.h"
#include "UObject/Object.h"
#include "MediaPipePluginSettings.generated.h"

/**
 * 
 */
UCLASS()
class MEDIAPIPE_API UMediaPipePluginSettings : public UObject
{
	GENERATED_BODY()
public:
	UMediaPipePluginSettings();

	/**
	 * MediaPipe4U Remoting OSC protocol service port.
	 */
	UPROPERTY(EditAnywhere, Category="Remoting", DisplayName="OSC Port", meta=(ClampMin=1025, ClampMax=65535, ToolTip="MediaPipe4U Remoting OSC protocol service port."))
	int RemotingOSCPort = 22345;

	UPROPERTY(EditAnywhere, Category="Remoting", DisplayName="Protocols Enabled", meta=(ToolTip="Enable MediaPipe4U Remoting service."))
	ERemotingProtocols RemotingProtocolsEnabled = ERemotingProtocols::OSC;

	UPROPERTY(EditAnywhere, Category="Remoting", DisplayName="Auto Start", meta=(ToolTip="Whether or not the remoting service will be automatically started on demand when we needed it."))
	bool bRemotingAutoStart = true;
	
	UPROPERTY(VisibleAnywhere, Category="Summary")
	FString Edition;

	UPROPERTY(VisibleAnywhere, Category="Summary")
	FString Version;

	UPROPERTY(VisibleAnywhere, Category="Summary")
	FString ProjectPage;

	UPROPERTY(VisibleAnywhere, Category="Document", DisplayName="文档 (简体中文)")
	FString CnDocument;

	UPROPERTY(VisibleAnywhere, Category="Document", DisplayName="English")
	FString EnDocument;

	UPROPERTY(VisibleAnywhere, Category="Environment", Transient)
	FString Project;

	UPROPERTY(VisibleAnywhere, Category="Environment", Transient)
	FString DeviceID;

	UPROPERTY(VisibleAnywhere, Category="License")
	FString Expiration;

	UPROPERTY(VisibleAnywhere, Category="License")
	FString AuthorizedTo;

	void RefreshLicenseInfo();

	int ExpirationDays = 0;
	EPluginEdition PluginEdition;
};
