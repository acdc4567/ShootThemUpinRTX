// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ShootThemUp : ModuleRules
{
	public ShootThemUp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay","Niagara" ,"PhysicsCore","GameplayTasks","NavigationSystem"});

		PublicIncludePaths.AddRange(new string[] { 
		"ShootThemUp/Public/Player"
		,"ShootThemUp/Public/Components"
		,"ShootThemUp/Public/Dev"
		,"ShootThemUp/Public/Weapon"
		,"ShootThemUp/Public/UI"
		,"ShootThemUp/Public/Animation"
		,"ShootThemUp/Public/Pickups"
		,"ShootThemUp/Public/Weapon/Components"
		,"ShootThemUp/Public/AI"
		,"ShootThemUp/Public/AI/Tasks"
		,"ShootThemUp/Public/AI/Services"
		,"ShootThemUp/Public/AI/EQS"
		});
	
	}
}
