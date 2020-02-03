// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Agent_RGameMode.h"
#include "Agent_RCharacter.h"
#include "UObject/ConstructorHelpers.h"


AAgent_RGameMode::AAgent_RGameMode()

{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	
}



