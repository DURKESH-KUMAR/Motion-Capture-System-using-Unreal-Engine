using System.IO;
using UnrealBuildTool;

public class MiniZip : ModuleRules
{
    public MiniZip(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;

        bool setup = false;
        
        
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            // AddEngineThirdPartyPrivateStaticDependencies(Target,"zlib");
            //
            // if (Target.Platform == UnrealTargetPlatform.Win64)
            // {
            //     PublicDefinitions.Add("ZLIB_WINAPI");
            // }
            
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "Win64", "zlib.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "Win64", "bzip2.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "Win64", "liblzma.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "Win64", "libminizip.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "Win64", "zstd_static.lib"));
            setup = true;
        }

        if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "Linux", "libminizip.a"));
            setup = true;
        }

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "Android", "arm64-v8a", "libminizip.a"));
            setup = true;
        }

        if (setup)
        {
            PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));
        }
    }
}