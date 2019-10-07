// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "SlAiBTDecoratorBase.generated.h"

/**
 * 
 */
UCLASS()
class SLAICOURSE_API USlAiBTDecoratorBase : public UBTDecorator
{
	GENERATED_BODY()
	
	//对应的就是蓝图节点的PerformConditionCheck
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
	
};
