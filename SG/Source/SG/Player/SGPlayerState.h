// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerState.h"
#include "SGPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SG_API ASGPlayerState : public APlayerState
{
	GENERATED_BODY()
	
	// AKnightCharacter, APlayerCharacter에서 AMyUEPlayerState의 private, protected에 접근 가능.
	friend class AKnightCharacter;
	friend class APlayerCharacter;

public:
	ASGPlayerState();

public:
	void InitPlayer();

public:
	float GetCameraZoomMin() const { return mCameraZoomMin; }
	float GetCameraZoomMax() const { return mCameraZoomMax; }


protected:
	// Transient: 저장/로드가 안될 때 사용
	UPROPERTY(Transient)
	float	mCameraZoomMin;

	UPROPERTY(Transient)
	float	mCameraZoomMax;

	UPROPERTY(Transient)
	float	mCameraZoomDistance;
};
