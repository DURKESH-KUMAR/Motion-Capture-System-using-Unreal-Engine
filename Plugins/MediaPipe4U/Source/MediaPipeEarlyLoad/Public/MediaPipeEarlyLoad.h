// Copyright (c) 2025 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"


class MEDIAPIPEEARLYLOAD_API FMediaPipeEarlyLoadModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    TArray<void*> DllHandles;
};
