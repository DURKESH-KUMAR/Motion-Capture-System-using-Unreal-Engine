// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
using UnrealBuildTool;
using System.IO;

public class MediaPipeLiveLink : ModuleRules
{
	public MediaPipeLiveLink(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.NoPCHs;
		bUsePrecompiled = true;
		PrecompileForTargets = PrecompileTargetsType.None;
		
		if (!bUsePrecompiled)
		{
			string mediapipeDirectory = GetModuleDirectory("MediaPipe");
			string headerFolder = Path.Combine(mediapipeDirectory, "Private", "License");
			PrivateIncludePaths.Add(headerFolder);
		}
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", 
				"CoreUObject",
				"MediaPipe",
				"MediaPipeMotion", 
				"LiveLinkInterface",
				"AugmentedReality"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Engine",
				"Slate",
				"SlateCore", 
				"JsonUtilities",
				"InputDevice",
				"MediaPipe",
				"MediaPipeMotion", 
				// "Networking",
				// "Sockets",
				"OSC"
				// ... add private dependencies that you statically link with here ...	
			}
		);

		if (!bUsePrecompiled)
		{
			PrivateIncludePathModuleNames.AddRange(new string[] { "MediaPipe" });
		}
	}
}
