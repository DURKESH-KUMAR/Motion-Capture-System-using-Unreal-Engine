// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once
#include "PluginEdition.h"
#include "Dom/JsonValue.h"
#include "LicenseInfo.generated.h"

USTRUCT()
struct MEDIAPIPE_API FLicenseInfo
{
	FLicenseInfo(const FLicenseInfo& Other)
		: AuthorizedTo(Other.AuthorizedTo),
		  AuthorizedPolicy(Other.AuthorizedPolicy),
		  Edition(Other.Edition),
		  Expired(Other.Expired),
		  LicenseKey(Other.LicenseKey),
		  LicenseVersion(Other.LicenseVersion),
		  Features(Other.Features),
		  FeaturesList(Other.FeaturesList),
		  Fields(Other.Fields),
		  Content(Other.Content)
	{
	}

	FLicenseInfo(FLicenseInfo&& Other) noexcept
		: AuthorizedTo(std::move(Other.AuthorizedTo)),
		  AuthorizedPolicy(std::move(Other.AuthorizedPolicy)),
		  Edition(Other.Edition),
		  Expired(Other.Expired),
		  LicenseKey(std::move(Other.LicenseKey)),
		  LicenseVersion(std::move(Other.LicenseVersion)),
		  Features(std::move(Other.Features)),
		  FeaturesList(std::move(Other.FeaturesList)),
		  Fields(std::move(Other.Fields)),
		  Content(std::move(Other.Content))
	{
	}

	FLicenseInfo& operator=(const FLicenseInfo& Other)
	{
		if (this == &Other)
			return *this;
		AuthorizedTo = Other.AuthorizedTo;
		AuthorizedPolicy = Other.AuthorizedPolicy;
		Edition = Other.Edition;
		Expired = Other.Expired;
		LicenseKey = Other.LicenseKey;
		LicenseVersion = Other.LicenseVersion;
		Features = Other.Features;
		FeaturesList = Other.FeaturesList;
		Fields = Other.Fields;
		Content = Other.Content;
		return *this;
	}

	FLicenseInfo& operator=(FLicenseInfo&& Other) noexcept
	{
		if (this == &Other)
			return *this;
		AuthorizedTo = std::move(Other.AuthorizedTo);
		AuthorizedPolicy = std::move(Other.AuthorizedPolicy);
		Edition = Other.Edition;
		Expired = Other.Expired;
		LicenseKey = std::move(Other.LicenseKey);
		LicenseVersion = std::move(Other.LicenseVersion);
		Features = std::move(Other.Features);
		FeaturesList = std::move(Other.FeaturesList);
		Fields = std::move(Other.Fields);
		Content = std::move(Other.Content);
		return *this;
	}
	FLicenseInfo(){}
	
	GENERATED_BODY()

	inline const static FString AuthorizedPolicyDevice = "Device";
	inline const static FString AuthorizedPolicyProject = "Project";
	
	UPROPERTY()
	FString AuthorizedTo = TEXT("EpicMarket");

	UPROPERTY()
	FString AuthorizedPolicy = TEXT("Standard");

	UPROPERTY()
	EPluginEdition Edition = EPluginEdition::Trial;

	UPROPERTY()
	int64 Expired = FDateTime::UtcNow().ToUnixTimestamp() + 30 * 24 * 60 * 60;

	UPROPERTY()
	FString LicenseKey;
	
	UPROPERTY()
	FString LicenseVersion = "v1";

	UPROPERTY()
	FString Features = "*";

	TArray<FName> FeaturesList;

	const FString& ToRawString() const;

	bool WriteToFile(const FString& LicenseFile, const FString& LicenseContent);
	
	bool ParseFromFile(const FString& LicenseFile);

	static FLicenseInfo& GetCurrent();

	bool IsInPeriod() const;

	FString GetLicensedProject() const;
	FString GetLicensedDevice() const;
	
private:
	mutable FCriticalSection RawStringLock;
	mutable FRWLock LicenseLock;
	TMap<FString, TSharedPtr<FJsonValue>> Fields;
	FString Content;
	mutable FString RawString;
};


enum class LicenseStatus
{
	Unknown,
	Valid,
	Invalid,
	FeatureForbidden
};
