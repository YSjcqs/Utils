// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class PlatformUtils : ModuleRules
{
	public string ThirdPartyDirectory
	{
		get
		{
			return Path.Combine(ModuleDirectory, "..", "ThirdParty");
		}
	}
	
	public string EngineBinariesDir
	{
		get
		{
			return Path.Combine(EngineDirectory, "Binaries", Target.Platform.ToString());
		}
	}

	public string NUIIncludeDirectory
	{
		get
		{
			if (Target.Platform == UnrealTargetPlatform.Android)
			{
				// return Path.Combine(ThirdPartyDirectory, "include");
			}
			else if(Target.Platform == UnrealTargetPlatform.IOS)
			{
				return Path.Combine(BinariesDirectory, "NuiUtils.framework", "Headers");
			}
			return Path.Combine(ThirdPartyDirectory, "Include");
		}
	}

	public string BinariesDirectory
	{
		get
		{
			if (Target.Platform == UnrealTargetPlatform.IOS)
			{
				return Path.Combine(ThirdPartyDirectory, "IOS");
			}
			else if (Target.Platform == UnrealTargetPlatform.Android)
			{
				return Path.Combine(ThirdPartyDirectory, "Android");
			}
			return Path.Combine(ThirdPartyDirectory, "Bin");
		}
	}

	public PlatformUtils(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"ApplicationCore",
			}
		);
		
		PublicIncludePaths.Add(ThirdPartyDirectory);
		if(Target.Platform == UnrealTargetPlatform.IOS)
		{
			PublicIncludePaths.Add(NUIIncludeDirectory);
			AdditionalPropertiesForReceipt.Add("IOSPlugin", Path.Combine(ModuleDirectory, "NativeIOSPlatform_UPL.xml"));
			PublicAdditionalFrameworks.Add(new Framework("NuiUtils", BinariesDirectory, "", true));
		}
		else if(Target.Platform == UnrealTargetPlatform.Android)
		{
			PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });
			AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(ModuleDirectory, "NativeAndroidPlatform_UPL.xml"));
		}
	}
}