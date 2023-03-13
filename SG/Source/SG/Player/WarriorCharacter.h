// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerCharacter.h"
#include "WarriorCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SG_API AWarriorCharacter : public APlayerCharacter
{
	GENERATED_BODY()
	
public:
	AWarriorCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void NormalAttackCheck();
};
