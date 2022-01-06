// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealRoguelikeTarget : TargetRules
{
	public UnrealRoguelikeTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames?.AddRange( new[] { "UnrealRoguelike" } );
	}
}
