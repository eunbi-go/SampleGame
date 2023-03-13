// Fill out your copyright notice in the Description page of Project Settings.


#include "SGPlayerController.h"

ASGPlayerController::ASGPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASGPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ASGPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ASGPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

void ASGPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ASGPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
