// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiEnemyTaskChaseSwitch.h"
#include "SlAiEnemyController.h"
#include "SlAiEnemyCharacter.h"
#include "AI/Navigation/NavigationSystem.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SlAiTypes.h"
#include "SlAiHelper.h"

EBTNodeResult::Type USlAiEnemyTaskChaseSwitch::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//如果初始化敌人参数不成功，直接返回失败
	if (!InitEnemyElement(OwnerComp)) return EBTNodeResult::Failed;
	//获取与玩家的距离
	float EPDistance = FVector::Distance(SECharacter->GetActorLocation(), SEController->GetPlayerLocation());
	//如果距离小于300，状态设置为攻击，跳出追逐状态
	if (EPDistance<300.f)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(EnemyState.SelectedKeyName, (uint8)EEnemyAIState::ES_Attack);

		return EBTNodeResult::Failed;
	}
	//如果大于1500了,跳到巡逻状态,并且设置没有锁定玩家
	if (EPDistance>1500.f)
	{
		//告诉控制器丢失了玩家
		SEController->LoosePlayer();
		//改状态为巡逻
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(EnemyState.SelectedKeyName, (uint8)EEnemyAIState::ES_Patrol);
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::Succeeded;
}
