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
	HP = 100.f;
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
	int AnimCount = Stream.RandRange(1, 4);
	//返回全部时长
	return AnimLength * AnimCount;
}

void ASlAiEnemyCharacter::OnSeePlayer(APawn * PlayerChar)
{
	if (Cast<ASlAiPlayerCharacter>(PlayerChar))
	{
		//SlAiHelper::Debug(FString("I See Player!"));
	}
}
