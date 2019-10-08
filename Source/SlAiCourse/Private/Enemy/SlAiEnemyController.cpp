// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiEnemyController.h"
#include "Kismet/GameplayStatics.h"
#include "SlAiPlayerCharacter.h"
#include "SlAiEnemyCharacter.h"

#include "SlAiEnemyBlackboard.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "TimerManager.h"
#include "SlAiTypes.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "SlAiHelper.h"


ASlAiEnemyController::ASlAiEnemyController()
{
	PrimaryActorTick.bCanEverTick = true;
}


void ASlAiEnemyController::BeginPlay()
{
	Super::BeginPlay();

	//初始化玩家指针，此指针一直存在
	SPCharacter = Cast<ASlAiPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GWorld, 0));
	if (!SPCharacter) return;
	//如果角色没有初始化
	if (!SECharacter) SECharacter = Cast<ASlAiEnemyCharacter>(GetPawn());

	//初始设定没有锁定玩家
	IsLockPlayer = false;
}

void ASlAiEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//如果玩家指针和角色指针存在
	if (SECharacter&&SPCharacter) SECharacter->UpdateHPBarRotation(SPCharacter->GetCameraPos());

}
#if 1
void ASlAiEnemyController::Possess(APawn * InPawn)
{
	//绝对一定必须要调用父类函数
	Super::Possess(InPawn);

	//实例化一下角色
	SECharacter = Cast<ASlAiEnemyCharacter>(InPawn);
	
	//获取行为树资源
	UBehaviorTree* StaticBehaviorTreeObject = LoadObject<UBehaviorTree>(NULL, TEXT("BehaviorTree'/Game/Blueprint/Enemy/EnemyBehaviorTree.EnemyBehaviorTree'"));
	//这里为什么要复制一个资源，如果只放一个敌人在场景中，那么上面就可以，但是多个敌人，那么就得再写下下面代码
	UBehaviorTree* BehaviorTreeObject = DuplicateObject<UBehaviorTree>(StaticBehaviorTreeObject, NULL);
	//如果资源不存在,直接返回
	if (!BehaviorTreeObject) return;
	BehaviorTreeObject->BlackboardAsset = DuplicateObject<USlAiEnemyBlackboard>((USlAiEnemyBlackboard*)StaticBehaviorTreeObject->BlackboardAsset, NULL);

	//开始绑定
	BlackboardComp = Blackboard;

	bool IsSuccess = true;

	if (BehaviorTreeObject->BlackboardAsset && (Blackboard == nullptr || Blackboard->IsCompatibleWith(BehaviorTreeObject->BlackboardAsset) == false))
	{
		IsSuccess = UseBlackboard(BehaviorTreeObject->BlackboardAsset, BlackboardComp);
	}
	if (IsSuccess)
	{
		BehaviorComp = Cast<UBehaviorTreeComponent>(BrainComponent);
		if (!BehaviorComp)
		{
			BehaviorComp = NewObject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
			BehaviorComp->RegisterComponent();
		}
		BrainComponent = BehaviorComp;
		check(BehaviorComp != NULL);

		BehaviorComp->StartTree(*BehaviorTreeObject, EBTExecutionMode::Looped);

		// 设置预状态为巡逻
		BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Patrol);

		//修改敌人的初始移动速度是100
		SECharacter->SetMaxSpeed(100.f);

		// 设置预状态为巡逻方式二
		/*int32 EnemyStateIndex = BlackboardComp->GetKeyID("EnemyState");
		BlackboardComp->SetValue<UBlackboardKeyType_Enum>(EnemyStateIndex, (UBlackboardKeyType_Enum::FDataType)EEnemyAIState::ES_Patrol);*/
	}

	/**
	**
	开始绑定代码是参考这个函数的源代码
	*/
	//RunBehaviorTree(BehaviorTreeObject);

}

void ASlAiEnemyController::UnPossess()
{
	Super::UnPossess();

	//停止行为树
	if (BehaviorComp) BehaviorComp->StopTree();
}
#endif
FVector ASlAiEnemyController::GetPlayerLocation() const
{
	if (SPCharacter) return SPCharacter->GetActorLocation();
	return FVector::ZeroVector;
}

bool ASlAiEnemyController::IsPlayerDead()
{
	if (SPCharacter) return SPCharacter->IsPlayerDead();
	return false;
}

void ASlAiEnemyController::OnSeePlayer()
{

	//如果已经锁定了玩家或者玩家死亡，不再执行下面行动
	if (IsLockPlayer || IsPlayerDead()) return;
	//设置锁定玩家
	IsLockPlayer = true;
	//修改预状态为追逐
	BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Chase);
	//修改敌人速度
	SECharacter->SetMaxSpeed(300.f);
}

void ASlAiEnemyController::LoosePlayer()
{
	//设置丢失玩家的锁定
	IsLockPlayer = false;
}
