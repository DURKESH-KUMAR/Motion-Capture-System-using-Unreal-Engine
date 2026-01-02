// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
using UnrealBuildTool;
using System.IO;

public class MediaPipeEditor : ModuleRules
{
    public const string BinaryOutputDir = "$(BinaryOutputDir)";

    public MediaPipeEditor(ReadOnlyTargetRules target) : base(target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bUseUnity = false;
        //bUseRTTI = true;
        bUsePrecompiled = true;
        PrecompileForTargets = PrecompileTargetsType.Any;


        PublicDependencyModuleNames.AddRange(
                new string[] {
                    "Core",
                    "SlateCore",
                    "Slate",
                    "MediaPipe",
                }
            );

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "Projects",
                "AnimGraph",
                "BlueprintGraph",
                "MediaPipe", 
                "PropertyEditor",
                "UnrealEd", 
                //"Persona", 
                "MainFrame",
                "EditorStyle",
                "ContentBrowser",
                "DesktopPlatform",
                "Json",
                "JsonUtilities",
                "InputCore",
                "ToolMenus", 
                "PlacementMode", 
                "WorkspaceMenuStructure",
                "ToolWidgets",
                "MaterialEditor",
                "SharedSettingsWidgets", 
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
