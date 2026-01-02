// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
using UnrealBuildTool;

public class MediaPipeNvAREditor : ModuleRules
{
    public MediaPipeNvAREditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs; 
        bUsePrecompiled = true;
        PrecompileForTargets = PrecompileTargetsType.None;
        
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "MediaPipeNvAR"
            }
        );
    }
}
