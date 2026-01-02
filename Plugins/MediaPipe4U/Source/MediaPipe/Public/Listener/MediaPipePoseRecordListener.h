// // Copyright (c) 2025 Anders Xiao. All rights reserved.
// // https://github.com/endink
// // Create: 2025-04-08

#pragma once
#include "MediaPipeHolisticListener.h"

class MEDIAPIPE_API FMediaPipePoseRecordListener : public FMediaPipeHolisticListener
{
public:
	FMediaPipePoseRecordListener(const FString& Folder);
	virtual void OnStarted() override;
	virtual void OnStopped() override;
	virtual void OnPoseWorldLandmarks(const TSharedPtr<FMediaPipeLandmarkList>& Landmarks) override;
private:
	FString SaveFileFolder;
	IFileHandle* FileHandle = nullptr;
};
