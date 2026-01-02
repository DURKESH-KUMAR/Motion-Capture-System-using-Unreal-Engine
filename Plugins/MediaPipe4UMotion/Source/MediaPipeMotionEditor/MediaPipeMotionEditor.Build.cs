// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
using UnrealBuildTool;
using System.IO;

public class MediaPipeMotionEditor : ModuleRules
{
    public const string BinaryOutputDir = "$(BinaryOutputDir)";

    public MediaPipeMotionEditor(ReadOnlyTargetRules target) : base(target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        //bUseUnity = false;
        //bUseRTTI = true;
        bUsePrecompiled = true;
        PrecompileForTargets = PrecompileTargetsType.Any;


        PublicDependencyModuleNames.AddRange(
                new string[] {
                    "Core",
                    "SlateCore",
                    "Slate",
                    "AnimGraph",
                    "MediaPipeMotion", 
                    "ControlRigDeveloper"
                }
            );

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "AnimGraph",
                "BlueprintGraph",
                "AssetTools",
                "PropertyEditor",
                "UnrealEd", 
                "Persona", 
                "MainFrame",
                "AssetRegistry",
                "EditorStyle",
                "ContentBrowser",
                "DesktopPlatform",
                "Json",
                "JsonUtilities",
                "ControlRig",
                "GraphEditor",
                "InputCore",
                "ToolMenus", 
                "PlacementMode", 
                "WorkspaceMenuStructure",
                "ToolWidgets",
                "MaterialEditor",
                "SharedSettingsWidgets", 
                "ControlRigEditor",
                "MediaPipe",
                "MediaPipeEditor",
                "MediaPipeMotion", 
                // "EditorFramework",
                // "Kismet",
                // "RigVMDeveloper",
                // "GraphEditor",
                // "ApplicationCore",
                //"ControlRigEditor",
                //"ControlRigDeveloper", 
            }
        );
        
        // if (Target.bBuildEditor)
        // {
        //     PrivateIncludePathModuleNames.Add("ControlRigEditor");
        //     DynamicallyLoadedModuleNames.Add("ControlRigEditor");
        // }


    }

    
}
