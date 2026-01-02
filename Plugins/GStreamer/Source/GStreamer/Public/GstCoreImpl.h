#pragma once
#include "Containers/UnrealString.h"

#define GST_INTERFACE_IMPL(Name)\
	friend class FGstCoreImpl;\
	protected:\
	Name() {}\
	virtual ~Name() {}\
	public:\
	static Name* CreateInstance();\
	virtual void Destroy() = 0;\
	private:

class FGstCoreImpl
{
public:

	static bool Init(const FString& BinPath, const FString& PluginPath);
	static void Deinit();
};
