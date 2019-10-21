// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SlAiSaveGame.generated.h"

/**
 * ����дһ���ṹ�壬ֱ���ڽṹ�����о�������Ʒ�����Խṹ�����ʽ������savegame
 */
UCLASS()
class SLAICOURSE_API USlAiSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, Category = "SlAi")
		FVector PlayerLocation;

	UPROPERTY(VisibleAnywhere, Category = "SlAi")
		float PlayerHP;

	UPROPERTY(VisibleAnywhere, Category = "SlAi")
		float PlayerHunger;
	//�ϳɱ��������ƷIndex
	UPROPERTY(VisibleAnywhere, Category = "SlAi")
		TArray<int32> InputIndex;
	//�ϳɱ��������Ʒ����
	UPROPERTY(VisibleAnywhere, Category = "SlAi")
		TArray<int32> InputNum;
	//������ƷIndex
	UPROPERTY(VisibleAnywhere, Category = "SlAi")
		TArray<int32> NormalIndex;
	//������Ʒ����
	UPROPERTY(VisibleAnywhere, Category = "SlAi")
		TArray<int32> NormalNum;
	//�������ƷIndex
	UPROPERTY(VisibleAnywhere, Category = "SlAi")
		TArray<int32> ShortcutIndex;
	//�������Ʒ����
	UPROPERTY(VisibleAnywhere, Category = "SlAi")
		TArray<int32> ShortcutNum;

	UPROPERTY(VisibleAnywhere, Category = "SlAi")
		TArray<FVector> EnemyLoaction;

	UPROPERTY(VisibleAnywhere, Category = "SlAi")
		TArray<float> EnemyHP;

	UPROPERTY(VisibleAnywhere, Category = "SlAi")
		TArray<FVector> ResourceRock;

	UPROPERTY(VisibleAnywhere, Category = "SlAi")
		TArray<FVector> ResourceTree;

	UPROPERTY(VisibleAnywhere, Category = "SlAi")
		TArray<FVector> PickupStone;

	UPROPERTY(VisibleAnywhere, Category = "SlAi")
		TArray<FVector> PickupWood;
	
	
};
