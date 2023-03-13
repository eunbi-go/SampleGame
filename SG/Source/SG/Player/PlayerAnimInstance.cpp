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
	// �÷��̾��� �̵� �ӵ� ������ ���.
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
	// ���� ���ϴ� ������ ��� ����.
	if (!mIsNormalAttackEnable)
		return;

	// ���� ���� �����ҰŴϱ� �� ���� ���������� ���� ����.
	PrintViewport(1.f, FColor::Red, TEXT("start attack"));
	mIsNormalAttackEnable = false;

	if (!Montage_IsPlaying(mNormalAttackMontageArray[mNormalAttackIndex]))
	{

		// 0.f: ���� ��ġ ����.
		Montage_SetPosition(mNormalAttackMontageArray[mNormalAttackIndex], 0.f);

		// ��Ÿ�� ���.
		Montage_Play(mNormalAttackMontageArray[mNormalAttackIndex]);

		// 0, 1, 2, 3 �ݺ�
		mNormalAttackIndex = (mNormalAttackIndex + 1) % mNormalAttackMontageArray.Num();

		// ���� ������.
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
	// ���� ���� ���� �̾ �ص� ��.
	mIsNormalAttackEnable = true;
}

void UPlayerAnimInstance::AnimNotify_AttackEnd()
{
	// ������ �������� �ٽ� ó������ ������ �� �ֵ��� ���� ���� �ʱ�ȭ.
	mNormalAttackIndex = 0;
	mIsNormalAttackEnable = true;
	mIsNormalAttack = false;
}
