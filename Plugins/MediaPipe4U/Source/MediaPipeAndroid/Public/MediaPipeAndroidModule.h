// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
#pragma once
#include "Modules/ModuleInterface.h"

class MEDIAPIPEANDROID_API FMediaPipeAndroidModule : public IModuleInterface {
public:
  /** IModuleInterface implementation */
  virtual void StartupModule() override;
  virtual void ShutdownModule() override;

  static FMediaPipeAndroidModule& Get();
};
