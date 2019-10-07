// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiEnemyTaskBase.h"
#include "SlAiEnemyController.h"
#include "SlAiEnemyCharacter.h"

bool USlAiEnemyTaskBase::InitEnemyElement(UBehaviorTreeComponent& OwnerComp)
{
	//如果已经初始化了,直接return,避免重复调用
	if (SEController && SECharacter) return true;
	//进行赋值
	SEController = Cast<ASlAiEnemyController>(OwnerComp.GetAIOwner());
	if (SEController) {
		SECharacter = Cast<ASlAiEnemyCharacter>(SEController->GetPawn());
		if (SECharacter) return true;
	}
	return false;
}


