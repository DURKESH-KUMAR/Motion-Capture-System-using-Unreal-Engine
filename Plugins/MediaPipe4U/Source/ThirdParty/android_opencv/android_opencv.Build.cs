// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
using System;
using System.IO;
using UnrealBuildTool;

public class android_opencv : ModuleRules
{
	public const string BinaryOutputDir = "$(BinaryOutputDir)";
	
	public android_opencv(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			string opencv = Path.Combine(ModuleDirectory, "lib", "Android", "arm64-v8a", "libopencv_world.so");
			
			PublicAdditionalLibraries.Add(opencv);
			PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));
			
			string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
			AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "android_opencv_APL.xml"));
		}
	}
}
