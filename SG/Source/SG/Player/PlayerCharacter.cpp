// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "SGPlayerState.h"
#include "PlayerAnimInstance.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// CreateDefaultSubobject: 컴포넌트 생성.
	// - 템플릿으로 생성할 타입을 지정하고 인자로 이름을 지정한다.
	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// SpringArm을 Mesh의 Child로 지정한다.
	mSpringArm->SetupAttachment(GetMesh());

	// Camera 컴포넌트를 SpringArm 컴포넌트의 자식 컴포넌트로 붙여준다.
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
		// 아무 키도 누르지 않은 상태. 움직이지X.
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
	// 카메라만 회전시킨다.
	//--------------------------

	if (Scale == 0.f)
		return;

	// 회전 가능한 각도에 제한을 둔다.
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
	// 플레이어 자체를 회전시킨다.
	//--------------------------

	if (Scale == 0.f)
		return;

	AddControllerYawInput(Scale * 180.0f * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::CameraZoom(float Scale)
{
	if (Scale == 0.f)
		return;

	// 너무 가까이 가지 않도록 제한한다.
	// - 5.f는 변수로 만들어두는 것이 좋다.
	mSpringArm->TargetArmLength += (Scale * -5.f);


	// 타입이 맞으면 해당 타입 메모리 주소를 형변환하여 반환. 아니면 nullptr 반환.
	ASGPlayerState* state = Cast<ASGPlayerState>(GetPlayerState());


	// 기본값 세팅 후, 만약 플레이어 상태 클래스가 존재한다면 
	// 플레이어 상태 클래스에서 값을 받아서 사용한다.
	// -> AMyUEPlayerState: 플레이어 상태 저장용 클래스. (플레이어 관련 변수 저장)
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

