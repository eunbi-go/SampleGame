// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "SGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SG_API ASGPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASGPlayerController();

protected:
	virtual void BeginPlay() override;

	// ������Ʈ���� ��� �ʱ�ȭ�� ���� ȣ��Ǵ� �Լ�
	virtual void PostInitializeComponents() override;

protected:
	// �÷��̾� ��Ʈ�ѷ��� Pawn�� ���ǵ� �� ȣ��
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

public:
	virtual void Tick(float DeltaTime) override;
};
