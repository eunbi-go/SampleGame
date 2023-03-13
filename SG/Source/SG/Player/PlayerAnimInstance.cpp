// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"

#include "PlayerCharacter.h"


UPlayerAnimInstance::UPlayerAnimInstance()
{
	mMoveDirection = 0.f;
	mSpeedRatio = 0.f;

	mIsNormalAttackEnable = true;
	mIsNormalAttack = false;
	mNormalAttackIndex = 0;
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

void UPlayerAnimInstance::NormalAttack()
{
	// 공격 못하는 상태일 경우 리턴.
	if (!mIsNormalAttackEnable)
		return;

	// 이제 공격 시작할거니까 이 공격 끝날때까지 공격 못함.
	PrintViewport(1.f, FColor::Red, TEXT("start attack"));
	mIsNormalAttackEnable = false;

	if (!Montage_IsPlaying(mNormalAttackMontageArray[mNormalAttackIndex]))
	{

		// 0.f: 시작 위치 지정.
		Montage_SetPosition(mNormalAttackMontageArray[mNormalAttackIndex], 0.f);

		// 몽타주 재생.
		Montage_Play(mNormalAttackMontageArray[mNormalAttackIndex]);

		// 0, 1, 2, 3 반복
		mNormalAttackIndex = (mNormalAttackIndex + 1) % mNormalAttackMontageArray.Num();

		// 현재 공격중.
		mIsNormalAttack = true;
	}
	else
		mIsNormalAttackEnable = true;
}

void UPlayerAnimInstance::AnimNotify_Attack()
{
	APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(playerCharacter))
	{
		playerCharacter->NormalAttackCheck();
	}
}

void UPlayerAnimInstance::AnimNotify_AttackEnable()
{
	// 이제 다음 공격 이어서 해도 됨.
	mIsNormalAttackEnable = true;
}

void UPlayerAnimInstance::AnimNotify_AttackEnd()
{
	// 공격이 끝났으니 다시 처음부터 공격할 수 있도록 공격 상태 초기화.
	mNormalAttackIndex = 0;
	mIsNormalAttackEnable = true;
	mIsNormalAttack = false;
}
