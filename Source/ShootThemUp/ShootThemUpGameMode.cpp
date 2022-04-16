// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootThemUpGameMode.h"
#include "ShootThemUpCharacter.h"
#include "UObject/ConstructorHelpers.h"

AShootThemUpGameMode::AShootThemUpGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
