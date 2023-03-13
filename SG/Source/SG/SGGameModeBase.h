// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SGGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SG_API ASGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASGGameModeBase();

public:
	// 실행 순서: InitGame()-> PostLogin()-> BeginPlay
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrMessage) override;
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};
