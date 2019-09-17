// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiPlayerController.h"
#include "SlAiHandObject.h"
#include "SlAiPlayerState.h"
#include "SlAiPlayerCharacter.h"
#include "CollisionQueryParams.h"
#include "Components/LineBatchComponent.h"
#include "Camera/CameraComponent.h"
#include "SlAiResourceObject.h"
#include "SlAiPickupObject.h"

#include "Engine/Engine.h"


ASlAiPlayerController::ASlAiPlayerController()
{
	//允许每帧运行
	PrimaryActorTick.bCanEverTick = true;
}

void ASlAiPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//射线检测
	RunRayCast();
	//处理动作状态
	StateMachine();
}

void ASlAiPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//获取角色与状态
	if (!SPCharacter) SPCharacter = Cast<ASlAiPlayerCharacter>(GetCharacter());
	if (!SPState) SPState = Cast<ASlAiPlayerState>(PlayerState);
	
	//设置鼠标不显示
	bShowMouseCursor = false;
	//设置输入模式
	FInputModeGameOnly InputMode;
	InputMode.SetConsumeCaptureMouseDown(true);
	SetInputMode(InputMode);

	//设置预动作
	LeftUpperType = EUpperBody::Punch;
	RightUpperType = EUpperBody::PickUp;

	IsLeftButtonDown = false;
	IsRightButtonDown = false;
}

void ASlAiPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//绑定视角切换
	InputComponent->BindAction("ChangeView", IE_Pressed, this, &ASlAiPlayerController::ChangeView);
	//绑定鼠标按下事件
	InputComponent->BindAction("LeftEvent", IE_Pressed, this, &ASlAiPlayerController::LeftEventStart);
	InputComponent->BindAction("LeftEvent", IE_Released, this, &ASlAiPlayerController::LeftEventStop);
	InputComponent->BindAction("RightEvent", IE_Pressed, this, &ASlAiPlayerController::RightEventStart);
	InputComponent->BindAction("RightEvent", IE_Released, this, &ASlAiPlayerController::RightEventStop);
	//绑定鼠标滚轮事件
	InputComponent->BindAction("ScrollUp", IE_Pressed, this, &ASlAiPlayerController::ScrollUpEvent);
	InputComponent->BindAction("ScrollDown", IE_Pressed, this, &ASlAiPlayerController::ScrollDownEvent);
}

void ASlAiPlayerController::ChangeHandObject()
{
	//生成手持物品
	SPCharacter->ChangeHandObject(ASlAiHandObject::SpawnHandObject(SPState->GetCurrentHandObjectIndex()));
}

void ASlAiPlayerController::ChangeView()
{
	//如果不允许切换视角，直接返回
	if (!SPCharacter->IsAllowSwitch) return;

	switch (SPCharacter->GameView)
	{
	case EGameViewMode::First:
		SPCharacter->ChangeView(EGameViewMode::Third);
		break;
	case EGameViewMode::Third:
		SPCharacter->ChangeView(EGameViewMode::First);
		break;
	}
}

void ASlAiPlayerController::LeftEventStart()
{
	IsLeftButtonDown = true;
	SPCharacter->UpperType = LeftUpperType;
}

void ASlAiPlayerController::LeftEventStop()
{
	IsLeftButtonDown = false;
	SPCharacter->UpperType = EUpperBody::None;
}

void ASlAiPlayerController::RightEventStart()
{
	IsRightButtonDown = true;
	SPCharacter->UpperType = RightUpperType;
}

void ASlAiPlayerController::RightEventStop()
{
	IsRightButtonDown = false;
	SPCharacter->UpperType = EUpperBody::None;
}

void ASlAiPlayerController::ScrollUpEvent()
{
	//如果不允许切换，直接返回
	if (!SPCharacter->IsAllowSwitch) return;

	//如果鼠标有在按键，则不准跳转
	if (IsLeftButtonDown || IsRightButtonDown) return;
	//告诉状态类切换快捷栏容器
	SPState->ChooseShortcut(true);
	//切换手中持有物品
	ChangeHandObject();

}

void ASlAiPlayerController::ScrollDownEvent()
{
	//如果不允许切换，直接返回
	if (!SPCharacter->IsAllowSwitch) return;

	//如果鼠标有在按键，则不准跳转
	if (IsLeftButtonDown || IsRightButtonDown) return;
	//告诉状态类切换快捷栏容器
	SPState->ChooseShortcut(false);
	//切换手中持有物品
	ChangeHandObject();
}

void ASlAiPlayerController::ChangePreUpperType(EUpperBody::Type RightType)
{
	//根据当前手持物品的类型来修改预动作
	switch (SPState->GetCurrentObjectType())
	{
	case EObjectType::Normal:
		LeftUpperType = EUpperBody::Punch;
		RightUpperType = RightType;
		break;
	case EObjectType::Food:
		LeftUpperType = EUpperBody::Punch;
		//如果右键状态是拾取那就给拾取，拾取优先级高
		RightUpperType = RightType == EUpperBody::None ? EUpperBody::Eat : RightType;
		break;
	case EObjectType::Tool:
		LeftUpperType = EUpperBody::Hit;
		RightUpperType = RightType;
	case EObjectType::Weapon:
		LeftUpperType = EUpperBody::Fight;
		RightUpperType = RightType;
		break;
	}
}

FHitResult ASlAiPlayerController::RayGetHitResult(FVector TraceStart, FVector TraceEnd)
{
	//FCollisionQueryParams TraceParams(true);//参数变量
	FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("TraceParams")), true, this);
	TraceParams.AddIgnoredActor(SPCharacter);//添加忽略的对象
	TraceParams.bTraceAsyncScene = true;//射线异步场景
	TraceParams.bReturnPhysicalMaterial = false;//是否返回物理材质
	//TraceParams.bTraceComplex = true;//检测混合碰撞
	
	FHitResult Hit(ForceInit);
	if (GetWorld()->LineTraceSingleByChannel(Hit,TraceStart,TraceEnd,ECollisionChannel::ECC_GameTraceChannel1,TraceParams))
	{
		DrawRayLine(TraceStart, TraceEnd, 5.f);
	}
	return Hit;
}

void ASlAiPlayerController::DrawRayLine(FVector StartPos, FVector EndPos, float Duration)
{
	ULineBatchComponent* const LineBatcher = GetWorld()->PersistentLineBatcher;
	if (LineBatcher != nullptr)
	{
		float LineDuration = (Duration > 0.f) ? Duration : LineBatcher->DefaultLifeTime;
		LineBatcher->DrawLine(StartPos, EndPos, FLinearColor::Red, 10, 0.f, LineDuration);
	}
}

void ASlAiPlayerController::RunRayCast()
{
	FVector StartPos(0.f);
	FVector EndPos(0.f);

	switch (SPCharacter->GameView)
	{
	case EGameViewMode::First:
		StartPos = SPCharacter->FirstCamera->K2_GetComponentLocation();
		EndPos = StartPos + SPCharacter->FirstCamera->GetForwardVector()*2000.f;
		break;
	case EGameViewMode::Third:
		StartPos = SPCharacter->ThirdCamera->K2_GetComponentLocation();
		StartPos = StartPos + SPCharacter->ThirdCamera->GetForwardVector()*300.f;
		EndPos = StartPos + SPCharacter->ThirdCamera->GetForwardVector()* 2000.f;
		break;
	}

	//是否检测到物品
	bool IsDetected = false;
	FHitResult Hit = RayGetHitResult(StartPos, EndPos);
	RayActor = Hit.GetActor();

	if (Cast<ASlAiPickupObject>(RayActor))
	{
		IsDetected = true;
		SPState->RayInfoText = Cast<ASlAiPickupObject>(RayActor)->GetInfoText();
	}
	if (Cast<ASlAiResourceObject>(RayActor))
	{
		IsDetected = true;
		SPState->RayInfoText = Cast<ASlAiResourceObject>(RayActor)->GetInfoText();
	}
	//如果什么都没有检测到就设置信息为无
	if (!IsDetected)
	{
		SPState->RayInfoText = FText();
	}
}
#if 1
void ASlAiPlayerController::StateMachine()
{
	//普通模式
	ChangePreUpperType(EUpperBody::None);
	if (!Cast<ASlAiResourceObject>(RayActor) && !Cast<ASlAiPickupObject>(RayActor))
	{
		//准星显示未锁定
		UpdatePointer.ExecuteIfBound(false, 1.f);
	}
	//如果检测到资源
	if (Cast<ASlAiResourceObject>(RayActor))
	{

		//如果左键没有按下，在资源模式下右键没有特殊意义
		if (!IsLeftButtonDown) {
			//准星锁定模式
			UpdatePointer.ExecuteIfBound(false, 0.f);
		}
		//如果左键已经按下
		if (IsLeftButtonDown&& FVector::Distance(RayActor->GetActorLocation(),SPCharacter->GetActorLocation())<SPState->GetAffectRange())
		{
			//获取实际伤害
			int Damage = SPState->GetDamageValue(Cast<ASlAiResourceObject>(RayActor)->GetResourceType());
			//让资源受到伤害并且获取剩余血量百分比
			float Range = Cast<ASlAiResourceObject>(RayActor)->TakeObjectDamage(Damage)->GetHPRange();
			//更新准星
			UpdatePointer.ExecuteIfBound(true, Range);
	
		}

	}
	//如果检测到可拾取物品,并且两者的距离小于300
	if (Cast<ASlAiPickupObject>(RayActor) && FVector::Distance(RayActor->GetActorLocation(), SPCharacter->GetActorLocation()) < 300.f)
	{
		//改变右键预状态为拾取
		ChangePreUpperType(EUpperBody::PickUp);
		//修改准星锁定模式
		UpdatePointer.ExecuteIfBound(false, 0);
		//如果右键按下
		if (IsRightButtonDown ) {
			//把物品捡起来
			Cast<ASlAiPickupObject>(RayActor)->TakePickup();
		}
	}
}
#endif