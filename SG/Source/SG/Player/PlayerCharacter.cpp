// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "SGPlayerState.h"
#include "PlayerAnimInstance.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// CreateDefaultSubobject: ������Ʈ ����.
	// - ���ø����� ������ Ÿ���� �����ϰ� ���ڷ� �̸��� �����Ѵ�.
	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// SpringArm�� Mesh�� Child�� �����Ѵ�.
	mSpringArm->SetupAttachment(GetMesh());

	// Camera ������Ʈ�� SpringArm ������Ʈ�� �ڽ� ������Ʈ�� �ٿ��ش�.
	mCamera->SetupAttachment(mSpringArm);

	mSpringArm->TargetArmLength = 500.f;
	mSpringArm->SetRelativeLocation(FVector(0.0, 0.0, 160.0));
	mSpringArm->SetRelativeRotation(FRotator(-15.0, 90.0, 0.0));

	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);

	bUseControllerRotationYaw = true;

	mMoveForwardDirection = 0.f;
	mCurMovingDir = EMovingDir::NOT_MOVING;
	mPreMovingDir = EMovingDir::NOT_MOVING;
	mTime = 0.f;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
		
	mAnimInst = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis<APlayerCharacter>(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis<APlayerCharacter>(TEXT("MoveHorizontal"), this, &APlayerCharacter::MoveHorizontal);
	PlayerInputComponent->BindAxis<APlayerCharacter>(TEXT("RotationCameraZ"), this, &APlayerCharacter::RotationCameraZ);
	PlayerInputComponent->BindAxis<APlayerCharacter>(TEXT("RotationCameraY"), this, &APlayerCharacter::RotationCameraY);
	PlayerInputComponent->BindAxis<APlayerCharacter>(TEXT("CameraZoom"), this, &APlayerCharacter::CameraZoom);
}

void APlayerCharacter::MoveForward(float Scale)
{
	mMoveForwardDirection = Scale;

	if (Scale == 0.f)
		return;

	AddMovementInput(GetActorForwardVector(), Scale);
}

void APlayerCharacter::MoveHorizontal(float Scale)
{
	float moveDir = 0.f;
	float preDir = mAnimInst->GetMoveDirection();

	if (mPreMovingDir == mCurMovingDir)
	{
		mTime += GetWorld()->GetDeltaSeconds();
		if (mTime >= 1.f) mTime = 1.f;
	}
	else
	{
		mPreMovingDir = mCurMovingDir;
		mTime = 0.f;
	}

	// W
	if (mMoveForwardDirection == 1.f)
	{
		// W
		if (Scale == 0.f)
		{
			mCurMovingDir = EMovingDir::W;
			moveDir = FMath::Lerp(preDir, 0.f, mTime);
			mAnimInst->SetMoveDirection(moveDir);
		}

		// W + D
		else if (Scale == 1.f)
		{
			mCurMovingDir = EMovingDir::WD;
			moveDir = FMath::Lerp(preDir, 45.f, mTime);
			mAnimInst->SetMoveDirection(moveDir);
		}

		// W + A
		else if (Scale == -1.f)
		{
			mCurMovingDir = EMovingDir::WA;
			moveDir = FMath::Lerp(preDir, -45.f, mTime);
			mAnimInst->SetMoveDirection(moveDir);
		}
	}

	// S
	else if (mMoveForwardDirection == -1)
	{
		// S
		if (Scale == 0.f)
		{
			mCurMovingDir = EMovingDir::S;
			moveDir = FMath::Lerp(preDir, 180.f, mTime);
			mAnimInst->SetMoveDirection(moveDir);
		}

		// S + D
		else if (Scale == 1.f)
		{
			moveDir = FMath::Lerp(preDir, 135.f, mTime);
			mCurMovingDir = EMovingDir::SD;
			mAnimInst->SetMoveDirection(moveDir);
		}

		// S + A
		else if (Scale == -1.f)
		{
			moveDir = FMath::Lerp(preDir, -135.f, mTime);
			mCurMovingDir = EMovingDir::SA;
			mAnimInst->SetMoveDirection(moveDir);
		}
	}

	else
	{
		// �ƹ� Ű�� ������ ���� ����. ��������X.
		if (Scale == 0.f)
		{
			mCurMovingDir = EMovingDir::NOT_MOVING;
			moveDir = FMath::Lerp(preDir, 0.f, mTime);
			mAnimInst->SetMoveDirection(moveDir);
		}

		// D
		else if (Scale == 1.f)
		{
			mCurMovingDir = EMovingDir::D;
			moveDir = FMath::Lerp(preDir, 90.f, mTime);
			mAnimInst->SetMoveDirection(moveDir);
		}

		// A
		else if (Scale == -1.f)
		{
			mCurMovingDir = EMovingDir::A;
			moveDir = FMath::Lerp(preDir, -90.f, mTime);
			mAnimInst->SetMoveDirection(moveDir);
		}
	}
	
	PrintViewport(1.f, FColor::Red, FString::Printf(TEXT("dir: %f"), moveDir));

	if (Scale == 0.f)
		return;

	AddMovementInput(GetActorRightVector(), Scale);
}

void APlayerCharacter::RotationCameraY(float Scale)
{
	//--------------------------
	// ī�޶� ȸ����Ų��.
	//--------------------------

	if (Scale == 0.f)
		return;

	// ȸ�� ������ ������ ������ �д�.
	FRotator rotator = mSpringArm->GetRelativeRotation();

	if (rotator.Pitch >= 40.f)
		mSpringArm->SetRelativeRotation(FRotator(40.f, rotator.Yaw, rotator.Roll));
	else if (rotator.Pitch <= -40.f)
		mSpringArm->SetRelativeRotation(FRotator(-40.f, rotator.Yaw, rotator.Roll));

	mSpringArm->AddRelativeRotation(FRotator(Scale * 180.f * GetWorld()->GetDeltaSeconds(), 0.f, 0.f));
}

void APlayerCharacter::RotationCameraZ(float Scale)
{
	//--------------------------
	// �÷��̾� ��ü�� ȸ����Ų��.
	//--------------------------

	if (Scale == 0.f)
		return;

	AddControllerYawInput(Scale * 180.0f * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::CameraZoom(float Scale)
{
	if (Scale == 0.f)
		return;

	// �ʹ� ������ ���� �ʵ��� �����Ѵ�.
	// - 5.f�� ������ �����δ� ���� ����.
	mSpringArm->TargetArmLength += (Scale * -5.f);


	// Ÿ���� ������ �ش� Ÿ�� �޸� �ּҸ� ����ȯ�Ͽ� ��ȯ. �ƴϸ� nullptr ��ȯ.
	ASGPlayerState* state = Cast<ASGPlayerState>(GetPlayerState());


	// �⺻�� ���� ��, ���� �÷��̾� ���� Ŭ������ �����Ѵٸ� 
	// �÷��̾� ���� Ŭ�������� ���� �޾Ƽ� ����Ѵ�.
	// -> AMyUEPlayerState: �÷��̾� ���� ����� Ŭ����. (�÷��̾� ���� ���� ����)
	float cameraZoomMin = 100.f;
	float cameraZoomMax = 500.f;

	if (IsValid(state))
	{
		cameraZoomMin = state->GetCameraZoomMin();
		cameraZoomMax = state->GetCameraZoomMax();
	}


	if (mSpringArm->TargetArmLength < cameraZoomMin)
		mSpringArm->TargetArmLength = cameraZoomMin;

	if (mSpringArm->TargetArmLength > cameraZoomMax)
		mSpringArm->TargetArmLength = cameraZoomMax;
}

