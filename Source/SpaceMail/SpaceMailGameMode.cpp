// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpaceMailGameMode.h"
#include "SpaceMailCharacter.h"

ASpaceMailGameMode::ASpaceMailGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = ASpaceMailCharacter::StaticClass();	
}
