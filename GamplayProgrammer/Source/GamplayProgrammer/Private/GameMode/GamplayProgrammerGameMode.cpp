// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "GamplayProgrammerGameMode.h"
#include "GamplayProgrammerHUD.h"
#include "BaseCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGamplayProgrammerGameMode::AGamplayProgrammerGameMode()
	: Super()
{
	// use our custom Pawn class
	DefaultPawnClass = ABaseCharacter::StaticClass();
	// use our custom HUD class
	HUDClass = AGamplayProgrammerHUD::StaticClass();
}
