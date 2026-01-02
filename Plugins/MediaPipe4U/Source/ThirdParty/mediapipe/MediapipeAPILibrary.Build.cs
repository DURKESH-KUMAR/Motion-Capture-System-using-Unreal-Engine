// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
using System;
using System.IO;
using EpicGames.Core;
using UnrealBuildTool;


public class MediapipeAPILibrary : ModuleRules
{
	public const string BinaryOutputDir = "$(BinaryOutputDir)";
	
	public MediapipeAPILibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;
		
		

		string MPDataDir = Path.Combine(ModuleDirectory, "Data");

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			string apiDll = Path.Combine(ModuleDirectory, "lib", "Win64", "mediapipe_api.dll");

			AddDLL(apiDll);
		}

		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
			AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "libmediapipe_APL.xml"));
		}
		
		if (Target.Platform == UnrealTargetPlatform.Linux)
		{
			string apiDll = Path.Combine(ModuleDirectory, "lib", "Linux", "libmediapipe_api.so");

			AddDLL(apiDll);
		}

		if (Target.Type != TargetType.Editor)
		{
			AddDepFolder(MPDataDir);
		}
	}
	
	private void CopyToBinaries(string filepath)
	{
		Log.WriteLine(LogEventType.Log, $"Deploy MediaPipe File: {filepath}");
		string binariesDir =  Path.Combine(PluginDirectory, "../../Binaries/Win64");;
		string filename = Path.GetFileName(filepath);

		if (!Directory.Exists(binariesDir))
			Directory.CreateDirectory(binariesDir);
		
		File.Copy(filepath, Path.Combine(binariesDir, filename), true);
	}

	private void CopyDirectory(string sourceDir, string destinationDir, bool recursive)
	{
		// Get information about the source directory
		var dir = new DirectoryInfo(sourceDir);

		// Check if the source directory exists
		if (!dir.Exists)
			throw new DirectoryNotFoundException("Source directory not found");

		// Cache directories before we start copying
		DirectoryInfo[] dirs = dir.GetDirectories();

		// Create the destination directory
		Directory.CreateDirectory(destinationDir);

		// Get the files in the source directory and copy to the destination directory
		foreach (FileInfo file in dir.GetFiles())
		{
			string targetFilePath = Path.Combine(destinationDir, file.Name);
			file.CopyTo(targetFilePath,true);
		}

		// If recursive and copying subdirectories, recursively call this method
		if (recursive)
		{
			foreach (DirectoryInfo subDir in dirs)
			{
				string newDestinationDir = Path.Combine(destinationDir, subDir.Name);
				CopyDirectory(subDir.FullName, newDestinationDir, true);
			}
		}
	}

	

	private void AddDLL(string sourceFile)
	{
		string fileName = Path.GetFileName(sourceFile);
		PublicDelayLoadDLLs.Add(fileName);
		string dst = "$(TargetOutputDir)/ThirdParty/" + fileName;
		RuntimeDependencies.Add(dst, sourceFile);
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
