// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include <functional>

#include "MediaPipeTexture.h"
#include "ObjectSharedPtr.h"
#include "Containers/Queue.h"
#include "Net/Core/Misc/ResizableCircularQueue.h"


class MEDIAPIPE_API FDynamicTexture
{
public:
	DECLARE_DELEGATE_ThreeParams(FOnTextureCreated, UTexture2D*, int, int)
	struct DynamicSession
	{
		int Width = 0;
		int Height = 0;
		int Pitch = 0;
		bool bPixelAligned = false;
		TAtomic<int32> PoolSize = 0;
		TQueue<TSharedPtr<IMediaPipeOutFrame>, EQueueMode::Mpsc> TexturePool;
		MediaPipeImageFormat Format = MediaPipeImageFormat::UNKNOWN;
		EPixelFormat PixelFormat = PF_Unknown;
	};
public:
	FDynamicTexture();
	~FDynamicTexture();

	bool Enqueue(TSharedPtr<IMediaPipeOutFrame> InMat);
	void NextFrame();
	const TUObjectSharedPtr<UTexture2D>& GetTextureObject() const;

	FOnTextureCreated FuncTextureCreated;
	int GetWidth() const;
	int GetHeight() const;
	void Start();
	void Stop(bool bWaitToCompleted = true);
	bool HasFrame() const;

	bool bIsSized = false;
	int MaxPoolSize = 10;
private:
	bool Resize(TSharedPtr<DynamicSession> InSession, TSharedPtr<IMediaPipeOutFrame> Mat);
	void Release();
	void RenderCmd_CreateTexture(TSharedPtr<DynamicSession> InSession);
	void RenderCmd_UpdateTexture(TSharedPtr<DynamicSession> InSession, TSharedPtr<IMediaPipeOutFrame> Mat, bool bIsNew);

	TUObjectSharedPtr<UTexture2D> TextureObject = nullptr;
	TSharedPtr<DynamicSession> Session;
	FCriticalSection BufferMux;
	
	bool bIsStarted = false;
	bool bIsReleasing = false;
	std::atomic<bool> bIsBusying = false;
};
