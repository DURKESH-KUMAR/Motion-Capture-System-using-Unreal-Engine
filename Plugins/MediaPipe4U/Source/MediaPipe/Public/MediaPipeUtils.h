// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once
#include <functional>
#include <string>

#include "CoreMinimal.h"
#include "MediaPipePluginInfo.h"
#include "Components/Image.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Async/Async.h"
#include "UObject/StrongObjectPtr.h"
#include "Widgets/Layout/Anchors.h"
#include "MediaPipeUtils.generated.h"

#define BROADCAST_DELEGATE_IN_GAME_THREAD(Delegate) \
if(Delegate.IsBound()) \
{ \
	if(IsInGameThread()) \
	{ \
		Delegate.Broadcast(); \
	} \
	else \
	{ \
		AsyncTask(ENamedThreads::GameThread, [this]() \
		{ \
			if(Delegate.IsBound()) \
			{ \
				Delegate.Broadcast(); \
			} \
		}); \
	} \
}

#define BROADCAST_DELEGATE_ONE_PARAM_IN_GAME_THREAD(Delegate, Param) \
{ \
	auto __p = Param; \
	if(IsInGameThread()) \
	{ \
		if(Delegate.IsBound()) \
		{ \
			Delegate.Broadcast(__p); \
		} \
	} \
	else \
	{ \
		AsyncTask(ENamedThreads::GameThread, [this, __p]() \
		{ \
			if(Delegate.IsBound()) \
			{ \
				Delegate.Broadcast(__p); \
			} \
		}); \
	} \
}

#define BROADCAST_DELEGATE_TWO_PARAMS_IN_GAME_THREAD(Delegate, Param1, Param2) \
{ \
	auto __p1 = Param1; \
	auto __p2 = Param2; \
	if(IsInGameThread()) \
	{ \
		if(Delegate.IsBound()) \
		{ \
			Delegate.Broadcast(__p1, __p2); \
		} \
	} \
	else \
	{ \
		AsyncTask(ENamedThreads::GameThread, [this, __p1, __p2]() \
		{ \
			if(Delegate.IsBound()) \
			{ \
				Delegate.Broadcast(__p1, __p2); \
			} \
		}); \
	} \
}


#define BROADCAST_DELEGATE_THREE_PARAMS_IN_GAME_THREAD(Delegate, Param1, Param2, Param3) \
{ \
	auto __p1 = Param1; \
	auto __p2 = Param2; \
	auto __p3 = Param3; \
	if(IsInGameThread()) \
	{ \
		if(Delegate.IsBound()) \
		{ \
			Delegate.Broadcast(__p1, __p2, __p3); \
		} \
	} \
	else \
	{ \
		AsyncTask(ENamedThreads::GameThread, [this, __p1, __p2, __p3]() \
		{ \
			if(Delegate.IsBound()) \
			{ \
				Delegate.Broadcast(__p1, __p2, __p3); \
			} \
		}); \
	} \
}


struct FMediaPipeAnimInstanceProxy;

UENUM(BlueprintType)
enum class EAnchorPosition : uint8
{
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight,
	TopCenter,
	BottomCenter,
	MiddleCenter
};

UENUM(BlueprintType)
enum class EModificationMode : uint8
{
	Replace,
	Additive
};

USTRUCT(BlueprintType)
struct MEDIAPIPE_API FSizeInt
{
	GENERATED_BODY()
	
	int Width = 0;
	int Height = 0;

	FORCEINLINE bool IsEmpty() const { return Width == 0  && Height == 0; }

	static const FSizeInt& Zero();
};


UCLASS(meta=(BlueprintThreadSafe, ScriptName = "MediaPipeUtils"))
class MEDIAPIPE_API UMediaPipeUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
	static constexpr float NEAR_ZERO  = 1.e-4f;
	
	static FString PrintAsciiTable(const TArray<TArray<FString>>& Rows);
	static FString PrintAsciiTable(const TArray<FString>& Headers, const TArray<TArray<FString>>& Rows);

	static bool IsNearZero(float Value);
	
	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static bool IsPlaying();

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static bool IsInPlayedWorld(const UObject* ActorOrComponent);

	static UWorld* GetPlayedWorld();
	
	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static void SetLogDebug(bool Enabled);

	UFUNCTION(BlueprintPure, Category="MediaPipe", meta=(ReturnDisplayName = "Success"))
	static bool GetLocalIPAddress(FString& IPAddress);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static bool AnchorWidgetInCanvas(UWidget* Widget, int TextureWidth, int TextureHeight,
												float MaxImageWidthPercent, float MaxImageHeightPercent,
												EAnchorPosition AnchorPosition);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static bool SetTextureToImage(UImage* Image, UTexture2D* Texture, int TextureWidth, int TextureHeight,
	                                            float MaxImageWidthPercent, float MaxImageHeightPercent,
	                                            EAnchorPosition AnchorPosition);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static bool SetMaterialToImage(UImage* Image, UMaterialInstance* Material, int TextureWidth, int TextureHeight,
												float MaxImageWidthPercent, float MaxImageHeightPercent,
												EAnchorPosition AnchorPosition);

	

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static FString Base64Utf8Encode(const FString& Text);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static bool Base64Utf8Decode(const FString& EncodedText, FString& DecodedText);

	UFUNCTION(BlueprintPure, Category="MediaPipe")
	static FString FormatPlayerTime(int64 Millisecond);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static bool ListWebcams(TArray<FString>& OutNames, const FName& ProviderName = FName(TEXT("")));

	template<typename  T>
	static T* FindComponent(const UObject* WorldContextObject)
	{
		auto* c = FindComponent(T::StaticClass(), WorldContextObject);
		return c ? static_cast<T*>(c) : nullptr;
	}
	
	static UActorComponent* FindComponent(const TSubclassOf<UActorComponent>& ComponentClass, const UObject* WorldContextObject);


	// UFUNCTION(BlueprintCallable, Category="MediaPipe")
	// static UIKRigDefinition* CreateRigControl(const USkeletalMeshComponent* SkeletalMeshComponent, const FHumanoidBoneSettings& InSettings);
	//
	// UFUNCTION(BlueprintCallable, Category="MediaPipe")
	// static UIKRetargeter* CreateIKRetargeter(const FRuntimeRetargetSource& From, const FRuntimeRetargetSource& To);

	UFUNCTION(BlueprintPure, Category="MediaPipe")
	static bool IsInEditor();

	UFUNCTION(BlueprintPure, Category="MediaPipe")
	static bool IsShippingBuild();

	static FAnchors AnchorsFromPosition(const EAnchorPosition& Position);

	static FVector2D CalcPositionFromAnchor(const EAnchorPosition& Position, FVector2D Size); 


	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static bool GetResolutionLimitSize(EResolutionLimits Limitation, int& LimitedWidth, int& LimitedHeight);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static FVector2D CalcImageSize(int TextureWidth, int TextureHeight, float MaxImageWidthPercent,
	                                             float MaxImageHeightPercent, int ScreenWidth, int ScreenHeight);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static bool LimitSizeByResolution(int TextureWidth, int TextureHeight, EResolutionLimits Limitation, FSizeInt& LimitedSize);
	
	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static bool LimitSize(int TextureWidth, int TextureHeight, int MaxWidth, int MaxHeight, FSizeInt& LimitedSize);

	UFUNCTION(BlueprintPure, Category="MediaPipe")
	static FString GetDurationString(int64 Millisecond);

	UFUNCTION(BlueprintPure, Category="MediaPipe")
	static FMediaPipePluginInfo PluginInfo();

	static std::string ConvertToUTF8(const FString& Str);
	static FString ConvertFromUTF8(const std::string& Str);
	static FString ConvertFromUTF8(const char* Chars, int Length);

	template<typename T>
	FORCEINLINE static bool IsSafeReachable(const TWeakObjectPtr<T>& InObject) { return InObject.IsValid() && !InObject->HasAnyFlags(RF_BeginDestroyed | RF_FinishDestroyed) && !InObject->IsUnreachable(); }

	template<typename T>
	FORCEINLINE static bool IsSafeReachableStrong(const TStrongObjectPtr<T>& InObject) { return InObject.IsValid() && !InObject->HasAnyFlags(RF_BeginDestroyed | RF_FinishDestroyed) && !InObject->IsUnreachable(); }

	FORCEINLINE static bool IsSafeReachablePtr(const UObject* InObject) { return InObject && !InObject->HasAnyFlags(RF_BeginDestroyed | RF_FinishDestroyed) && !InObject->IsUnreachable(); }

	static void ConvertToUTF8Bytes(const FString& Str, TArray<uint8>& Output);

	static FString GetThirdPartyBinariesFolder(const FString& PluginName, const FString& ThirdPartyFolderName);

	/**
	 * @brief 
	 * @param Date always use __DATE__ marco
	 * @return 
	 */
	static FString GetCompiledTime(const char* Date);

	UFUNCTION(BlueprintCallable, Category="MediaPipe")
	static int64 GetTimeMills();

	UFUNCTION(BlueprintPure, Category="MediaPipe")
	static FString DisplayDataSize(int64 SizeInBytes);

	
};



