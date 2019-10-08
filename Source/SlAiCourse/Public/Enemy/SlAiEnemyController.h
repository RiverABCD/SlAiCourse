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

	virtual void Possess(APawn* InPawn) override;

	virtual void UnPossess() override;

	virtual void Tick(float DeltaTime) override;

	//获取玩家位置
	FVector GetPlayerLocation() const;

	//玩家是否已经死亡
	bool IsPlayerDead();

	//看到了玩家,由Character的OnSeePlayer调用
	void OnSeePlayer();

	//丢失玩家定位
	void LoosePlayer();

public:

	//是否锁定了玩家
	bool IsLockPlayer;

protected:

	virtual void BeginPlay() override;

private:
	//玩家指针
	class ASlAiPlayerCharacter* SPCharacter;
	//敌人角色指针
	class ASlAiEnemyCharacter* SECharacter;
	//黑板组件
	class UBlackboardComponent* BlackboardComp;

	class UBehaviorTreeComponent* BehaviorComp;
};
