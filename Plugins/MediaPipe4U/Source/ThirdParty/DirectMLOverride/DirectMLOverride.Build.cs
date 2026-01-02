// Copyright (c) 2022 Anders Xiao. All rights reserved.
// https://github.com/endink
using System.IO;
using UnrealBuildTool;

public class DirectMLOverride : ModuleRules
{
    public DirectMLOverride(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;
        
        if (Target.Platform != UnrealTargetPlatform.Win64)
        {
            return;
        }
        
        string platformDir = Target.Platform.ToString();
        
        string libFileName = Target.Platform == UnrealTargetPlatform.Linux ? "libdirectml.so" : "DirectML.dll";
        string libSubDir = Path.Combine("ThirdParty", "Override");
        string dbgDllFileName = Target.Platform == UnrealTargetPlatform.Linux ? "libdirectml.so" : "DirectML.Debug.dll";
        
        string binDirPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "lib", platformDir));
        
        
        PublicDelayLoadDLLs.Add(libFileName);
        PublicDefinitions.Add("DIRECTML_PATH=" + libSubDir);
        PublicDefinitions.Add("DIRECTML_LATEST_PATH=" + libSubDir);
        PublicDefinitions.Add("DIRECTML_FILE_NAME=" + libFileName);

        if (Target.Type == TargetType.Editor && Target.Configuration == UnrealTargetConfiguration.Debug)
        {
            RuntimeDependencies.Add(Path.Combine("$(TargetOutputDir)", libSubDir, dbgDllFileName), Path.Combine(binDirPath, dbgDllFileName));
        }
        else
        {
            RuntimeDependencies.Add(Path.Combine("$(TargetOutputDir)", libSubDir, libFileName), Path.Combine(binDirPath, libFileName));
        }

    }
}