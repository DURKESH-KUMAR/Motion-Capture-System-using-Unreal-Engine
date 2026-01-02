using System.IO;
using UnrealBuildTool;

public class MediaPipeAndroid : ModuleRules
{
    public MediaPipeAndroid(ReadOnlyTargetRules Target) : base(Target)
    {
        bUsePrecompiled = true;
        PCHUsage = PCHUsageMode.NoPCHs; 
        PrecompileForTargets = PrecompileTargetsType.Any;
        
        string mediapipeDirectory = GetModuleDirectory("MediaPipe");
        string headerFolder = Path.Combine(mediapipeDirectory, "Public", "Macros");
        PublicIncludePaths.Add(headerFolder);
				
		
        PrivateIncludePaths.AddRange(
            new string[] {
                // ... add other private include paths required here ...
            }
        );
			
		
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core"
                // ... add other public dependencies that you statically link with here ...
            }
        );
			
		
        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "RHI",
                "TraceLog",
                "RenderCore",
                "OpenGLDrv",
                // ... add private dependencies that you statically link with here ...	
            }
        );
		
		
        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
                // ... add any modules that your module loads dynamically here ...
            }
        );

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            //string ThirdParty = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/"));
            PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });
            string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "MediaPipe4UAndroid_APL.xml"));

        }
    }
}
