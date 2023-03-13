// Fill out your copyright notice in the Description page of Project Settings.


#include "WarriorCharacter.h"

AWarriorCharacter::AWarriorCharacter()
{
	//-----------------------------------------
	// ĳ���� �޽� �ε�
	//-----------------------------------------
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	KnightAsset(TEXT("SkeletalMesh'/Game/ParagonAurora/Characters/Heroes/Aurora/Meshes/Aurora.Aurora'"));

	if (KnightAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(KnightAsset.Object);
	}

	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -88.0));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));


	//-----------------------------------------
	// AnimInstance ����
	//-----------------------------------------
	static ConstructorHelpers::FClassFinder<UAnimInstance>	animClass(TEXT("AnimBlueprint'/Game/Blueprints/Player/Animation/ABP_Warrior.ABP_Warrior_C'"));

	if (animClass.Succeeded())
		GetMesh()->SetAnimInstanceClass(animClass.Class);
}

void AWarriorCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AWarriorCharacter::NormalAttackCheck()
{
}
