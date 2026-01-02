#pragma once
#include "Containers/UnrealString.h"

class MEDIAPIPE_API FOpenSSLHelper
{
public:
	static bool RSAVerifySignature(const FString& PubPem, const FString& Content, const FString& Signature);
	static FString RSASignature(const FString& PrivatePem, const FString& Content);

	static bool RSAVerifySignatureByPemFile(const FString& PublicPemFile, const FString& Content, const FString& Signature);
	static FString RSASignatureByPemFile(const FString& PrivatePemFile, const FString& Content);

	static bool RSAVerifySignature(const FString& Content, const FString& Signature);
	static FString RSASignature(const FString& Content);
};

