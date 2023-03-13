// Copyright Epic Games, Inc. All Rights Reserved.


#include "SGGameModeBase.h"
#include "Player/WarriorCharacter.h"
#include "Player/SGPlayerController.h"
#include "Player/SGPlayerState.h"

ASGGameModeBase::ASGGameModeBase()
{
	DefaultPawnClass = AWarriorCharacter::StaticClass();
	PlayerControllerClass = ASGPlayerController::StaticClass();
	PlayerStateClass = ASGPlayerState::StaticClass();
}

void ASGGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void ASGGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrMessage)
{
	Super::InitGame(MapName, Options, ErrMessage);
}

void ASGGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void ASGGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
