// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BlackboardData.h"
#include "SlAiEnemyBlackboard.generated.h"

/**
 * 
 */
UCLASS()
class SLAICOURSE_API USlAiEnemyBlackboard : public UBlackboardData
{
	GENERATED_BODY()
	
public:
	virtual void PostLoad() override;
	
	
};
