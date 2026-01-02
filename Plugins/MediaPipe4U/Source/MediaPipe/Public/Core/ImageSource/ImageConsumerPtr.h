// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "ImageConsumerProvider.h"

struct MEDIAPIPE_API FImageConsumerPtr
{
	FImageConsumerPtr();
	explicit FImageConsumerPtr(IImageConsumerProvider* InObject);
	explicit FImageConsumerPtr(const TSharedPtr<IImageConsumer>& ObjectConsumer);
public:
	IImageConsumer* Get() const;
	bool IsValid() const;
	FImageConsumerPtr& operator=(const FImageConsumerPtr& Ptr);
	bool operator==(const FImageConsumerPtr& Ptr) const;
private:
	TWeakObjectPtr<UObject> ConsumerProvider = nullptr;
	IImageConsumerProvider* Interface = nullptr;
	TSharedPtr<IImageConsumer> NativeConsumer = nullptr;
	bool bIsNative = false;
};

MEDIAPIPE_API uint32 GetTypeHash(const FImageConsumerPtr& Key);