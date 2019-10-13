// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiEnemyTaskAttackFollow.h"
#include "SlAiEnemyController.h"
#include "SlAiEnemyCharacter.h"
#include "AI/Navigation/NavigationSystem.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type USlAiEnemyTaskAttackFollow::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//如果初始化敌人参数不成功,直接返回失败
	if (!InitEnemyElement(OwnerComp)) return EBTNodeResult::Failed;
	//范围是5
	const float ChaseRadius = 5.f;
	//获取玩家到敌人之间的单位向量
	FVector SPToSE = SEController->GetPlayerLocation() - SECharacter->GetActorLocation();

	//获取距离
	float EPDistance = SPToSE.Size();

	//如果距离大于100.f,获取玩家与敌人连线上距离玩家100.f的那个点作为原始点来寻找导航点
	if (EPDistance > 100.f) {
		//归一化
		SPToSE.Normalize();
		//探索起点是玩家位置减去与敌人之间距离的一点点
		const FVector ChaseOrigin = SEController->GetPlayerLocation() - 100.f * SPToSE;
		//保存随机的位置
		FVector DesLoc(0.f);
		//使用导航系统获取随机点
		UNavigationSystem::K2_GetRandomReachablePointInRadius(SEController, ChaseOrigin, DesLoc, ChaseRadius);
		//修改目的地
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(Destination.SelectedKeyName, DesLoc);
	}
	else
	{
		//如果距离小于100.f,那么设置敌人当前的位置为目标位置
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(Destination.SelectedKeyName, SECharacter->GetActorLocation());
	}
	//返回成功
	return EBTNodeResult::Succeeded;

}
