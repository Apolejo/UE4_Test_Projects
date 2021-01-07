// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SaberPorto_TestHud.generated.h"

UCLASS(config = Game)
class ASaberPorto_TestHud : public AHUD
{
	GENERATED_BODY()

public:
	ASaberPorto_TestHud();

	/** Font used to render the vehicle info */
	UPROPERTY()
	UFont* HUDFont;

	// Begin AHUD interface
	virtual void DrawHUD() override;
	// End AHUD interface

};
