// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiEnemyTaskLocaESC.h"
#include "SlAiEnemyController.h"
#include "SlAiEnemyCharacter.h"
#include "AI/Navigation/NavigationSystem.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type USlAiEnemyTaskLocaESC::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//如果初始化敌人参数不成功,直接返回失败
	if (!InitEnemyElement(OwnerComp)) return EBTNodeResult::Failed;

	//范围是2000以内
	const float ChaseRadius = 2000.f;
	//获取敌人到玩家之间的向量
	FVector SPToSE = SECharacter->GetActorLocation() - SEController->GetPlayerLocation();
	//探索起点敌人位置
	const FVector ChaseOrigin = SECharacter->GetActorLocation();
	//保存随机的位置
	FVector DesLoc(0.f);
	//使用导航系统获取随机点
	UNavigationSystem::K2_GetRandomReachablePointInRadius(SEController, ChaseOrigin, DesLoc, ChaseRadius);
	//如果获得的位置到敌人的向量和玩家到敌人的向量的夹角大于90度,重新定义方向
	while (FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(SPToSE, DesLoc - SECharacter->GetActorLocation()))) > 90.f)
	{
		//使用导航系统重新获取随机点
		UNavigationSystem::K2_GetRandomReachablePointInRadius(SEController, ChaseOrigin, DesLoc, ChaseRadius);
	}
	//修改速度为300
	SECharacter->SetMaxSpeed(300.f);
	//修改目的地
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(Destination.SelectedKeyName, DesLoc);
	//返回成功
	return EBTNodeResult::Succeeded;
}
