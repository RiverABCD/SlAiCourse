// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiBTDecoratorBase.h"

//返回true的话，执行下一步任务，false则是返回父节点
bool USlAiBTDecoratorBase::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return true;
}


