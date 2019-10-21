// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SlAiSaveGame.generated.h"

/**
 * 可以写一个结构体，直接在结构体中列举以下物品，并以结构体的形式保存在savegame
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
	//合成表输入框物品Index
	UPROPERTY(VisibleAnywhere, Category = "SlAi")
		TArray<int32> InputIndex;
	//合成表输入框物品数量
	UPROPERTY(VisibleAnywhere, Category = "SlAi")
		TArray<int32> InputNum;
	//背包物品Index
	UPROPERTY(VisibleAnywhere, Category = "SlAi")
		TArray<int32> NormalIndex;
	//背包物品数量
	UPROPERTY(VisibleAnywhere, Category = "SlAi")
		TArray<int32> NormalNum;
	//快捷栏物品Index
	UPROPERTY(VisibleAnywhere, Category = "SlAi")
		TArray<int32> ShortcutIndex;
	//快捷栏物品数量
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
