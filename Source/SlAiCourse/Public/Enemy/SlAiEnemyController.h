// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "SlAiEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class SLAICOURSE_API ASlAiEnemyController : public AAIController
{
	GENERATED_BODY()
	
	
public:
	ASlAiEnemyController();

	virtual void Tick(float DeltaTime) override;

	//获取玩家位置
	FVector GetPlayerLocation() const;

protected:

	virtual void BeginPlay() override;

private:
	//玩家指针
	class ASlAiPlayerCharacter* SPCharacter;
	//敌人角色指针
	class ASlAiEnemyCharacter* SECharacter;
};
