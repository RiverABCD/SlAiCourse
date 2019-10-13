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

	//判定玩家是否在远离
	bool IsPlayerAway();

	//获取玩家指针
	UObject* GetPlayerPawn();

	//告诉控制器动作完成
	void ResetProcess(bool IsFinish);

	//接受伤害，传入剩余生命值
	void UpdateDamageRatio(float HPRatioVal);

	//完成伤害状态
	void FinishStateHurt();

	//完成防御动作的方法
	void FinishStateDefence();

	//死亡
	void EnemyDead();

	

public:

	//是否锁定了玩家
	bool IsLockPlayer;

protected:

	virtual void BeginPlay() override;
private:

	//更新状态序列
	void UpdateStatePama();

private:
	//玩家指针
	class ASlAiPlayerCharacter* SPCharacter;
	//敌人角色指针
	class ASlAiEnemyCharacter* SECharacter;
	//黑板组件
	class UBlackboardComponent* BlackboardComp;

	class UBehaviorTreeComponent* BehaviorComp;

	//保存与玩家的距离序列,保存8个,每半秒更新一次
	TArray<float> EPDisList;

	//时间委托句柄
	FTimerHandle EPDisHandle;

	//血值
	float HPRatio;

	//是否允许播放受伤状态
	bool IsAllowHurt;

	//受伤计时器
	float HurtTimeCount;
};
