// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once
#include "Widgets/M4UCommandContext.h"

class MEDIAPIPEMOTIONEDITOR_API FMediaPipeMotionSynchronizer
{
public:
	FM4UActionDelegate ComponentsLoadedDelegate;
	FM4UActionDelegate BeginUnloadComponentsDelegate;
	
	static FGuid SyncContext(
		const FM4UActionDelegate& OnMediaPipeComponentsLoaded,
		const FM4UActionDelegate& OnBeginUnloadMediaPipeComponents);

	static bool UnSyncContext(const FGuid& SynchronizerId);

	static const TMap<FGuid, TSharedPtr<const FMediaPipeMotionSynchronizer>>& GetSynchronizerList();
};
