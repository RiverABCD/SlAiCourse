// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiEnemyController.h"
#include "Kismet/GameplayStatics.h"
#include "SlAiPlayerCharacter.h"
#include "SlAiEnemyCharacter.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "TimerManager.h"


ASlAiEnemyController::ASlAiEnemyController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASlAiEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//如果玩家指针和角色指针存在
	if (SECharacter&&SPCharacter) SECharacter->UpdateHPBarRotation(SPCharacter->GetCameraPos());
	
}

void ASlAiEnemyController::BeginPlay()
{
	Super::BeginPlay();

	//初始化玩家指针，此指针一直存在
	SPCharacter = Cast<ASlAiPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GWorld, 0));
	//如果角色没有初始化
	if (!SECharacter) SECharacter = Cast<ASlAiEnemyCharacter>(GetPawn());
}

FVector ASlAiEnemyController::GetPlayerLocation() const
{
	if (SPCharacter) return SPCharacter->GetActorLocation();
	return FVector::ZeroVector;
}
