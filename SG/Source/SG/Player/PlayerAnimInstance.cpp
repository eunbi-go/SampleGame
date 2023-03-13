// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"

#include "PlayerCharacter.h"


UPlayerAnimInstance::UPlayerAnimInstance()
{
	mMoveDirection = 0.f;
	mSpeedRatio = 0.f;
}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//--------------------------
	// 플레이어의 이동 속도 비율을 계산.
	//--------------------------
	
	APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(playerCharacter))
	{
		UCharacterMovementComponent* movement = playerCharacter->GetCharacterMovement();

		mSpeedRatio = movement->Velocity.Size() / movement->MaxWalkSpeed;
	}
}
