// Copyright Epic Games, Inc. All Rights Reserved.

#include "Building_EscapeGameMode.h"
#include "Building_EscapeHUD.h"
#include "Building_EscapeCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABuilding_EscapeGameMode::ABuilding_EscapeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ABuilding_EscapeHUD::StaticClass();
}
