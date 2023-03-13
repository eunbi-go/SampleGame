// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"

#include "DrawDebugHelpers.h"	// ������ ���� ��� ����.
#include "EngineGlobals.h"
#include "Engine.h"

#include "UObject/NoExportTypes.h"
#include "GameInfo.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(SG, Log, All);

// �α� ����� ���� ��ũ�� ����: �Լ��̸�[�ٹ�ȣ]
//  __FUNCTION__: �Լ� �̸��� �����´�.
//  __LINE__: �ش� ���Ͽ����� �� ���� ������ ���´�.
// FString::FromInt(__LINE__): �� ��ȣ�� ������ ���ͼ� ���ڿ��� ������ش�.
#define	LOG_CALLINFO	(FString(__FUNCTION__) + TEXT("[") + FString::FromInt(__LINE__) + TEXT("]"))

// UE_LOG: �𸮾󿡼� �α� ����� ���� ���.
//  ...: �������ڸ� ����ϱ� ����. (������ ������ ���ϴ´�� �߰� ����)
//  %s: ���ڿ��� �޾ƿͼ� ��ü���ֱ� ���� ����Ѵ�. 
//		���ڿ� ������ �����ؾ� ��.
//		-> FString �տ� * �� �ٿ��� �������� �ϸ� FString�� ������ �ִ� ���ڿ� �����͸� ���´�,
//  __VA_ARGS__ : �������ڸ� ���´�.
#define	LOG(Format, ...)	UE_LOG(SG, Warning, TEXT("%s : %s"), *LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

#define	LOGSTRING(Str)		UE_LOG(SG, Warning, TEXT("%s : %s"), *LOG_CALLINFO, *Str)


// �������� ����Ʈ�� �α׸� ����ش�.
void PrintViewport(float Time, const FColor& Color, const FString& Text);





/**
 * 
 */
UCLASS()
class SG_API UGameInfo : public UObject
{
	GENERATED_BODY()
	
};
