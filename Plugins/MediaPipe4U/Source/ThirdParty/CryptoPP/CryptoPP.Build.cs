using UnrealBuildTool;
using System.IO;

public class CryptoPP : ModuleRules
{
    public const string BinaryOutputDir = "$(BinaryOutputDir)";

    public CryptoPP(ReadOnlyTargetRules Target) : base(Target)
    {
	    Type = ModuleType.External;
	    string modulePath = ModuleDirectory;
	    if (Target.Platform == UnrealTargetPlatform.Win64)
	    {
		    PublicAdditionalLibraries.Add(Path.Combine(modulePath, "lib", "cryptlib.lib"));
		    PublicIncludePaths.Add(Path.Combine(modulePath, "include"));
	    }
#if UE_5_5_OR_LATER
	    UndefinedIdentifierWarningLevel = WarningLevel.Off;
#else
	    bEnableUndefinedIdentifierWarnings = false;
#endif
	    bEnableExceptions = true;
	    //bUseRTTI = true;
    }
}
