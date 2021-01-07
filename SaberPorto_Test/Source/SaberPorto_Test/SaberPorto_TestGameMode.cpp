// Copyright Epic Games, Inc. All Rights Reserved.

#include "SaberPorto_TestGameMode.h"
#include "SaberPorto_TestPawn.h"
#include "SaberPorto_TestHud.h"
#include "MyCharacter.h"

ASaberPorto_TestGameMode::ASaberPorto_TestGameMode()
{
	DefaultPawnClass = AMyCharacter::StaticClass();
	HUDClass = ASaberPorto_TestHud::StaticClass();
}
