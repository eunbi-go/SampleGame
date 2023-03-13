// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

enum class EMovingDir : uint8
{
	W, A, S, D, WA, WD, SA, SD, NOT_MOVING
};

UCLASS()
class SG_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	void MoveForward(float Scale);
	void MoveHorizontal(float Scale);
	void RotationCameraY(float Scale);
	void RotationCameraZ(float Scale);
	void CameraZoom(float Scale);


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Component, meta = (AllowPrivateAccess = true))
		USpringArmComponent* mSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Component, meta = (AllowPrivateAccess = true))
		UCameraComponent* mCamera;

protected:
	class UPlayerAnimInstance* mAnimInst;

	// 현재 이동 방향.
	float	mMoveForwardDirection;
	EMovingDir	mCurMovingDir;
	EMovingDir	mPreMovingDir;
	float	mTime;
};
