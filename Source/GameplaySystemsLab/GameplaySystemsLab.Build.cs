// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameplaySystemsLab : ModuleRules
{
	public GameplaySystemsLab(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"GameplaySystemsLab",
			"GameplaySystemsLab/Variant_Platforming",
			"GameplaySystemsLab/Variant_Platforming/Animation",
			"GameplaySystemsLab/Variant_Combat",
			"GameplaySystemsLab/Variant_Combat/AI",
			"GameplaySystemsLab/Variant_Combat/Animation",
			"GameplaySystemsLab/Variant_Combat/Gameplay",
			"GameplaySystemsLab/Variant_Combat/Interfaces",
			"GameplaySystemsLab/Variant_Combat/UI",
			"GameplaySystemsLab/Variant_SideScrolling",
			"GameplaySystemsLab/Variant_SideScrolling/AI",
			"GameplaySystemsLab/Variant_SideScrolling/Gameplay",
			"GameplaySystemsLab/Variant_SideScrolling/Interfaces",
			"GameplaySystemsLab/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
