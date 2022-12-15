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
				return Path.Combine(NUIBinariesDirectory, "nuisdk.framework", "Headers");
			}
			return Path.Combine(ThirdPartyDirectory, "Include");
		}
	}

	public string NUIBinariesDirectory
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

	public string NUILibraryLinkNameBase
	{
		get
		{
			if(Target.Platform == UnrealTargetPlatform.Android)
			{
				return "nuisdk";
			}
			
			return string.Format("nuisdk-{0}-Shipping", Target.Platform.ToString());
		}
	}	

	public string NUIRuntimeLibraryFileName
	{
		get
		{
			if (Target.Platform == UnrealTargetPlatform.Mac)
			{
				return "lib" + NUILibraryLinkNameBase + ".dylib";
			}
			else if (Target.Platform == UnrealTargetPlatform.IOS)
			{
				return NUILibraryLinkNameBase + ".framework";
			}
			else if (Target.Platform == UnrealTargetPlatform.Android ||
			         Target.Platform.IsInGroup(UnrealPlatformGroup.Unix))
			{
				return "lib" + NUILibraryLinkNameBase + ".so";
			}
			else if (Target.Platform.IsInGroup(UnrealPlatformGroup.Microsoft))
			{
				return NUILibraryLinkNameBase + ".dll";
			}

			throw new BuildException("Unsupported platform");
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
			PublicAdditionalFrameworks.Add(new Framework("nuisdk", NUIBinariesDirectory, "", true));
		}
		else if(Target.Platform == UnrealTargetPlatform.Android)
		{
			PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });
			AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(ModuleDirectory, "NativeAndroidPlatform_UPL.xml"));
		}
		else
		{
			// RuntimeDependencies.Add(Path.Combine(EngineBinariesDir, NUIRuntimeLibraryFileName), Path.Combine(NUIBinariesDirectory, NUIRuntimeLibraryFileName));
			// PublicRuntimeLibraryPaths.Add(EngineBinariesDir);
			// PublicDelayLoadDLLs.Add(NUIRuntimeLibraryFileName);
		}
	}
}