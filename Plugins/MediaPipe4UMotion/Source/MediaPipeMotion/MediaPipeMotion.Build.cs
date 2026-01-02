// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

using System;
using UnrealBuildTool;
using System.IO;
using EpicGames.Core;


public class MediaPipeMotion : ModuleRules
{
    public const string BinaryOutputDir = "$(BinaryOutputDir)";

    public MediaPipeMotion(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs; // UseExplicitOrSharedPCHs;
        //bUseUnity = false;
        //bUseRTTI = true;
#if UE_5_5_OR_LATER
        UndefinedIdentifierWarningLevel = WarningLevel.Off;
#else
        bEnableUndefinedIdentifierWarnings = false;
#endif
        //bEnableExceptions = true;
        bUsePrecompiled = true;
        PrecompileForTargets = PrecompileTargetsType.None;
        
        PublicDependencyModuleNames.AddRange(
                new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "Projects",
                "MediaAssets",
                "UMG", 
                "LiveLinkInterface",
                "LiveLinkAnimationCore", 
                "ControlRig",
                "AugmentedReality",
                "MediaPipe"
                }
            );
        
    #if UE_5_2_OR_LATER
        PublicDependencyModuleNames.Add("RigVM");
    #endif

        if (Target.bBuildEditor)
        {
            PublicDependencyModuleNames.Add("ControlRigDeveloper");
        }
        
        // AddVcPackage("protobuf", true,
        //     "libprotobuf"
        // );
        
        
        if (!bUsePrecompiled)
        {
            string mediapipeDirectory = GetModuleDirectory("MediaPipe");
            string headerFolder = Path.Combine(mediapipeDirectory, "Private", "License");
            PrivateIncludePaths.Add(headerFolder);
        }
        
        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CUDAHeader",
                "CoreUObject",
                "HTTP",
                "InputCore",
                "RHI",
                "AnimationCore",
                "AnimGraphRuntime",
                "RenderCore",
                "MediaAssets",
                "AnimationCore",
                "Slate",
                "SlateCore",
                "UMG",
                "Media",
                "MediaUtils",
                "MediaPipe",
                "MediapipeAPILibrary",
                "MediaPipeAndroid",
                "OpenSSL",
                "Json",
                "JsonUtilities", 
                "IKRig",
                "Sockets",
            }
        );


        PublicIncludePaths.AddRange(
            new string[]
            {
                "$(ModuleDir)/Public/Core",
                "$(ModuleDir)/Public/Async",
                "$(ModuleDir)/Public/Animation",
                "$(ModuleDir)/Public/Core/Damping",
                "$(ModuleDir)/Public/Calibration",
                "$(ModuleDir)/Public/TwistCorrection",
                "$(ModuleDir)/Public/ControlRig", 
                "$(ModuleDir)/Public/LiveLink",
                
                "$(ModuleDir)/Public/Pose",
                "$(ModuleDir)/Public/Hand",
                "$(ModuleDir)/Public/Location",
                "$(ModuleDir)/Public/Ground", 
                
            });
        
        if (Target.bBuildEditor)
        {
            PrivateDependencyModuleNames.AddRange(new string[]{ "Settings", "UnrealEd" });
        }

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            OptimizeCode = CodeOptimization.Never;
            OptimizationLevel = OptimizationMode.Speed;
        }
    }
    
    

    private void AddDepFolder(string SourceDir)
    {
        foreach (string filePath in Directory.GetFiles(SourceDir, "*.*", SearchOption.AllDirectories))
        {
            string relativePah = Path.GetRelativePath(SourceDir, filePath);
            Log.WriteLine(LogEventType.Log, $"Find MediaPipe File: {relativePah}");
            string dst = Path.Combine(BinaryOutputDir, relativePah);
            RuntimeDependencies.Add(dst, filePath);
        }
    }
    
}
