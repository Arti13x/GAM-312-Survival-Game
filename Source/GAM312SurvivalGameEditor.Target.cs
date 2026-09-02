// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GAM312SurvivalGameEditorTarget : TargetRules
{
	public GAM312SurvivalGameEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V7;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_8;
		ExtraModuleNames.Add("GAM312SurvivalGame");
	}
}
