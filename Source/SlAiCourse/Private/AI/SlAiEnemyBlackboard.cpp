// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiEnemyBlackboard.h"
#include "SlAiTypes.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "SlAiPlayerCharacter.h"
#include "BehaviorTree/BlackboardData.h"

void USlAiEnemyBlackboard::PostLoad()
{
	Super::PostLoad();

	//目的地
	FBlackboardEntry Destination;
	Destination.EntryName = FName("Destination");
	UBlackboardKeyType_Vector* DestinationKeyType = NewObject<UBlackboardKeyType_Vector>();
	Destination.KeyType = DestinationKeyType;

	//敌人状态
	FBlackboardEntry EnemyState;
	EnemyState.EntryName = FName("EnemyState");
	UBlackboardKeyType_Enum* EnemyStateKeyType = NewObject<UBlackboardKeyType_Enum>();
	EnemyStateKeyType->EnumType = FindObject<UEnum>(ANY_PACKAGE, *FString("EEnemyAIState"), true);
	EnemyStateKeyType->EnumName = FString("EEnemyAIState");
	EnemyState.KeyType = EnemyStateKeyType;

	//等待时间
	FBlackboardEntry WaitTime;
	WaitTime.EntryName = FName("WaitTime");
	WaitTime.KeyType = NewObject<UBlackboardKeyType_Float>();

	Keys.Add(Destination);
	Keys.Add(EnemyState);
	Keys.Add(WaitTime);
}



