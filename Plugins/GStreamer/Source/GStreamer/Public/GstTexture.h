#pragma once

#include "GstAppSinkImpl.h"
#include "GstSampleImpl.h"
#include "Engine/Texture2D.h"
#include "GstVideoFormat.h"
#include "ITextureUpdateListener.h"
#include "SharedTexture2D.h"

class IGstTextureCallback
{
protected:
	~IGstTextureCallback() = default;
public:
	virtual void CbGstTextureCreated() = 0;
};

class FGstTexture : public TSharedFromThis<FGstTexture>
{
public:

	FGstTexture(const FString& Name, const TSharedPtr<IGstAppSink>& AppSink, IGstTextureCallback* Callback);
	virtual ~FGstTexture();
	virtual void Destroy();

	void SubmitSample(class IGstSample* Sample);
	void TickGameThread();
	void Release(bool bFlush = true);

	inline FSharedTexture2D& GetTextureObject() { return m_TextureObject; }
	inline EGstVideoFormat GetGstFormat() const { return m_GstFormat; }
	inline EPixelFormat GetUeFormat() const { return m_UeFormat; }
	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline void SetListener(ITextureUpdateListener* Listener) { UpdateListener = Listener; }
private:
	
	TSharedPtr<IGstSample> SwapSample(class IGstSample* NewSample);
	void ReleaseSample(class IGstSample* Sample) const;
	bool Resize(const TSharedPtr<IGstSample>& Sample);

	void CreateTexture();
	void RenderCmd_UpdateTexture(const TSharedPtr<IGstSample>& Sample);
	void UpdateTextureOnRenderThread(const TSharedPtr<IGstSample>& Sample);


	ITextureUpdateListener* UpdateListener = nullptr;
	FString m_Name;
	TSharedPtr<IGstAppSink> m_AppSink = nullptr;
	IGstTextureCallback* m_Callback = nullptr;
	FSharedTexture2D m_TextureObject = nullptr;

	TSharedPtr<IGstSample> m_Sample = nullptr;
	FCriticalSection m_SampleMx;

	EGstVideoFormat m_GstFormat = EGstVideoFormat::GST_VIDEO_FORMAT_UNKNOWN;
	EPixelFormat m_UeFormat = EPixelFormat::PF_Unknown;
	TextureCompressionSettings m_Compression = TextureCompressionSettings::TC_VectorDisplacementmap;
	int m_Width = 0;
	int m_Height = 0;
	int m_Pitch = 0;
	bool bDestroyed = false;

	double m_StatTimer = 0;
	int m_SampleCount = 0;
	int m_TickCount = 0;
	int m_EnqueCount = 0;
	int m_RenderCount = 0;
};
