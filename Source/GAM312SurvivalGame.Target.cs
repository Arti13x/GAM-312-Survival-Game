// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GAM312SurvivalGameTarget : TargetRules
{
	public GAM312SurvivalGameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V7;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8;
		ExtraModuleNames.Add("GAM312SurvivalGame");
	}
}
