// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink

using System;
using UnrealBuildTool;
using System.IO;
using EpicGames.Core;


public class MediaPipe : ModuleRules
{
    public const string BinaryOutputDir = "$(BinaryOutputDir)";

    public MediaPipe(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.NoPCHs; // UseExplicitOrSharedPCHs;
        bUseUnity = false;
        //bUseRTTI = true;
#if UE_5_5_OR_LATER
        UndefinedIdentifierWarningLevel = WarningLevel.Off;
#else
        bEnableUndefinedIdentifierWarnings = false;
#endif
        bEnableExceptions = true;
        bUsePrecompiled = true;
        PrecompileForTargets = PrecompileTargetsType.Any;
        
        PublicDependencyModuleNames.AddRange(
                new string[] {
                "Core",
                "Slate",
                "CoreUObject",
                "Engine",
                "Projects",
                "MediaAssets",
                "UMG", 
                "OSC",
                }
            );

        // AddVcPackage("protobuf", true,
        //     "libprotobuf"
        // );
        
        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CUDAHeader",
                "CoreUObject",
                "HTTP",
                "InputCore",
                "RHI",
                "RenderCore",
                "MediaAssets",
                "Slate",
                "SlateCore",
                "ApplicationCore",
                "UMG",
                "Media",
                "MediaUtils",
                "MediapipeAPILibrary",
                "MediaPipeAndroid",
                "OpenSSL",
                "Json",
                "JsonUtilities", 
                "Sockets",
                "MiniZip"
            }
        );

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PrivateDependencyModuleNames.AddRange(new string[] {
                "MediaPipeEarlyLoad"
            });
        }
        
        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PrivateDependencyModuleNames.AddRange(new string[] {
                "android_opencv"
            });
        }

        if (Target.Platform == UnrealTargetPlatform.Win64 || Target.Platform == UnrealTargetPlatform.Linux || Target.Platform == UnrealTargetPlatform.Mac)
        {
            PrivateDependencyModuleNames.AddRange(new string[]{ 
                "OpenCV", 
                "OpenCVHelper"
            });
        }
        if(Target.Platform == UnrealTargetPlatform.Android)
        {
            PublicSystemLibraries.Add("libjnigraphics");
            string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "MediaPipe_APL.xml"));
            
        }
        

        if (Target.bBuildEditor)
        {
            PrivateDependencyModuleNames.AddRange(new string[]{ "Settings", "UnrealEd" });
        }

        PublicIncludePaths.AddRange(
            new string[]
            {
                "$(ModuleDir)/Public/Core",
                "$(ModuleDir)/Public/Core/ImageSource",
                "$(ModuleDir)/Public/Core/CppUtils",
            });
        
        string licenseFolder = Path.Combine(ModuleDirectory, "license");
        Log.WriteLine(LogEventType.Log, $"License Directory: {licenseFolder}");
        AddDepFolder(licenseFolder);
        // protobuf deps
        
        PublicDefinitions.Add("MP_IMPORTS = 1");
        //
        PublicDefinitions.Add("M4U_VER_MAJOR=2025");
        PublicDefinitions.Add("M4U_VER_MINOR=0");
        PublicDefinitions.Add("M4U_VER_REVISION=1");

        FixCryptoPP();
    }

    private void FixCryptoPP()
    {
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            string engineCryptoModule = Path.Combine(EngineDirectory, @"Source/ThirdParty/CryptoPP/CryptoPP.Build.cs")
                .Replace('/', Path.DirectorySeparatorChar);
            
            if (File.Exists(engineCryptoModule))
            {
                Log.WriteLine(LogEventType.Log, "Source Unreal Engine found.");
                AddEngineThirdPartyPrivateStaticDependencies(Target,
                    "CryptoPP"
                );
                PrivateIncludePathModuleNames.Add("CryptoPP");
            }
            else
            {
                PrivateDependencyModuleNames.Add("CryptoPP");
            }
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
