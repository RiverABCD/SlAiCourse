// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiEnemyCharacter.h"
#include "ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "GameFramework/Pawn.h"
#include "SSlAiEnemyHPWidget.h"
#include "Perception/PawnSensingComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/ChildActorComponent.h"

#include "SlAiEnemyController.h"
#include "SlAiEnemyAnim.h"

#include "SlAiEnemyTool.h"
#include "SlAiHelper.h"
#include "SlAiPlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "SlAiDataHandle.h"
#include "SlAiFlobObject.h"
#include "SlAiTypes.h"


// Sets default values
ASlAiEnemyCharacter::ASlAiEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = ASlAiEnemyController::StaticClass();

	//设置碰撞体属性文件
	GetCapsuleComponent()->SetCollisionProfileName(FName("EnemyProfile"));
	GetCapsuleComponent()->bGenerateOverlapEvents = true;

	//添加模型
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> StaticEnemyMesh(TEXT("SkeletalMesh'/Game/Res/PolygonAdventure/Mannequin/Enemy/SkMesh/Enemy.Enemy'"));
	GetMesh()->SetSkeletalMesh(StaticEnemyMesh.Object);
	GetMesh()->SetCollisionObjectType(ECC_Pawn);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -95.f));
	GetMesh()->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0.f, 0.f, -90.f)));

	//添加动画蓝图
	static ConstructorHelpers::FClassFinder<UAnimInstance> StaticEnemyAnim(TEXT("AnimBlueprint'/Game/Blueprint/Enemy/Enemy_Animation.Enemy_Animation_C'"));
	GetMesh()->AnimClass = StaticEnemyAnim.Class;

	//实例化插槽
	WeaponSocket = CreateDefaultSubobject<UChildActorComponent>(TEXT("WeaponSocket"));
	ShieldSocket = CreateDefaultSubobject<UChildActorComponent>(TEXT("ShieldSocket"));

	//实例化血条
	HPBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBar"));
	HPBar->AttachTo(RootComponent);
	//HPBar->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("HeadTop_EndSocket"));
	//实例化敌人感知组件
	EnemySense = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("EnemySense"));

	//加载死亡动画资源
	AnimDead_I = Cast<UAnimationAsset>(StaticLoadObject(UAnimationAsset::StaticClass(), NULL, *FString("AnimSequence'/Game/Res/PolygonAdventure/Mannequin/Enemy/Animation/FightGroup/Enemy_Dead_I.Enemy_Dead_I'")));
	AnimDead_II = Cast<UAnimationAsset>(StaticLoadObject(UAnimationAsset::StaticClass(), NULL, *FString("AnimSequence'/Game/Res/PolygonAdventure/Mannequin/Enemy/Animation/FightGroup/Enemy_Dead_II.Enemy_Dead_II'")));

	//设置资源ID是3
	ResourceIndex = 3;
}


// Called when the game starts or when spawned
void ASlAiEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//获取动作引用
	SEAnim = Cast<USlAiEnemyAnim>(GetMesh()->GetAnimInstance());
	//控制器引用
	SEController = Cast<ASlAiEnemyController>(GetController());

	//绑定插槽
	WeaponSocket->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RHSocket"));
	ShieldSocket->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("LHSocket"));

	//给插槽添加物品
	WeaponSocket->SetChildActorClass(ASlAiEnemyTool::SpawnEnemyWeapon());
	ShieldSocket->SetChildActorClass(ASlAiEnemyTool::SpawnEnemySheild());

	//设置血条widget
	SAssignNew(HPBarWidget, SSlAiEnemyHPWidget);
	HPBar->SetSlateWidget(HPBarWidget);
	HPBar->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	HPBar->SetDrawSize(FVector2D(100.f, 10.f));
	//设置初始血量
	HP = 200.f;
	HPBarWidget->ChangeHP(HP / 200.f);

	//敌人感知参数设置
	EnemySense->HearingThreshold = 0.f;
	EnemySense->LOSHearingThreshold = 0.f;
	EnemySense->SightRadius = 1000.f;
	EnemySense->SetPeripheralVisionAngle(55.f);
	EnemySense->bHearNoises = false;
	//绑定看到玩家的方法
	FScriptDelegate OnSeePlayerDele;
	OnSeePlayerDele.BindUFunction(this, "OnSeePlayer");
	EnemySense->OnSeePawn.Add(OnSeePlayerDele);
}



void ASlAiEnemyCharacter::CreateFlobObject()
{
	TSharedPtr<ResourceAttribute> ResourceAttr = *SlAiDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);
	//遍历生成
	for (TArray<TArray<int>>::TIterator It(ResourceAttr->FlobObjectInfo); It; ++It)
	{
		//随机流
		FRandomStream Stream;
		//产生随机种子
		Stream.GenerateNewSeed();
		int Num = Stream.RandRange((*It)[1], (*It)[2]);

		if (GetWorld())
		{
			for (int i = 0; i < Num; ++i)
			{
				//生成掉落资源
				ASlAiFlobObject* FlobObject = GetWorld()->SpawnActor<ASlAiFlobObject>(GetActorLocation() + FVector(0.f, 0.f, 40.f), FRotator::ZeroRotator);
				FlobObject->CreateFlobObject((*It)[0]);
			}
		}
	}
}

// Called every frame
void ASlAiEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASlAiEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASlAiEnemyCharacter::UpdateHPBarRotation(FVector SPLoaction)
{
	FVector StartPos(GetActorLocation().X, GetActorLocation().Y, 0);
	FVector TargetPos(SPLoaction.X, SPLoaction.Y, 0.f);
	HPBar->SetWorldRotation(FRotationMatrix::MakeFromX(TargetPos - StartPos).Rotator());
}

void ASlAiEnemyCharacter::SetMaxSpeed(float Speed)
{
	//设置最大运动速度
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

float ASlAiEnemyCharacter::GetIdleWaitTime()
{
	//如果动作引用不存在，直接返回3秒
	if (!SEAnim) return 3.f;

	//创建随机流
	FRandomStream Stream;
	Stream.GenerateNewSeed();
	int IdleType = Stream.RandRange(0, 2);
	float AnimLength = SEAnim->SetIdelType(IdleType);
	//更新种子
	Stream.GenerateNewSeed();
	//产生动作次数
	int AnimCount = Stream.RandRange(1, 3);
	//返回全部时长
	return AnimLength * AnimCount;
}

float ASlAiEnemyCharacter::PlayAttackAction(EEnemyAttackType AttackType)
{
	//如果动作蓝图不存在，直接返回0s;
	if (!SEAnim) return 0.f;
	//返回攻击时长
	return SEAnim->PlayAttackAction(AttackType);
}



void ASlAiEnemyCharacter::AcceptDamage(int DamageVal)
{
	//进行血条更新
	HP = FMath::Clamp<float>(HP - DamageVal, 0.f, 500.f);
	HPBarWidget->ChangeHP(HP / 200.f);
	//如果血值小于0
	if (HP == 0&&!DeadHandle.IsValid())
	{
		//告诉控制器死亡
		SEController->EnemyDead();
		//停止所有动画
		SEAnim->StopAllAction();

		float DeadDuration = 0.f;
		FRandomStream Stream;
		Stream.GenerateNewSeed();
		int SelectIndex = Stream.RandRange(0, 1);
		if (SelectIndex == 0)
		{
			GetMesh()->PlayAnimation(AnimDead_I, false);
			DeadDuration = AnimDead_I->GetMaxCurrentTime() * 2;
		} 
		else
		{
			GetMesh()->PlayAnimation(AnimDead_II, false);
			DeadDuration = AnimDead_II->GetMaxCurrentTime() * 2;
		}

		//生成掉落物
		CreateFlobObject();

		//添加事件委托
		FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &ASlAiEnemyCharacter::DestroyEvent);
		GetWorld()->GetTimerManager().SetTimer(DeadHandle, TimerDelegate, DeadDuration, false);
	} 
	else
	{
		//告诉控制器收到伤害
		if (SEController) SEController->UpdateDamageRatio(HP / 200.f);
	}
}

float ASlAiEnemyCharacter::PlayHurtAction()
{
	//如果动作蓝图不存在直接返回0秒
	if (!SEAnim) return 0.f;
	//返回攻击时长
	return SEAnim->PlayHurtAction();
}

void ASlAiEnemyCharacter::StartDefence()
{
	//开启防御
	if (SEAnim) SEAnim->IsDefence = true;

}

void ASlAiEnemyCharacter::StopDefence()
{

}

void ASlAiEnemyCharacter::DestroyEvent()
{
	//销毁时间函数
	if (DeadHandle.IsValid()) GetWorld()->GetTimerManager().ClearTimer(DeadHandle);
	//销毁自己
	GetWorld()->DestroyActor(this);
}

FText ASlAiEnemyCharacter::GetInfoText() const
{
	TSharedPtr<ResourceAttribute> ResourceAttr = *SlAiDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);
	switch (SlAiDataHandle::Get()->CurrentCulture)
	{
	case ECultureTeam::EN:
		return ResourceAttr->EN;
		break;
	case ECultureTeam::ZH:
		return ResourceAttr->ZH;
		break;
	}
	return ResourceAttr->ZH;
}

void ASlAiEnemyCharacter::ChangeWeaponDetect(bool IsOpen)
{
	//如果手持物品存在,修改检测
	ASlAiEnemyTool* WeaponClass = Cast<ASlAiEnemyTool>(WeaponSocket->GetChildActor());
	if (WeaponClass) WeaponClass->ChangeOverlayDetect(IsOpen);
}

void ASlAiEnemyCharacter::OnSeePlayer(APawn * PlayerChar)
{
	if (Cast<ASlAiPlayerCharacter>(PlayerChar)){
		//SlAiHelper::Debug(FString("I See Player!"));
	}
	if (SEController) SEController->OnSeePlayer();
}
