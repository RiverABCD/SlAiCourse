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
#include "SlAiEnemyCharacter.h"
#include "TimerManager.h"
#include "SlAiTypes.h"


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
	//处理小地图更新
	TickMiniMap();
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
	//设置初始为Game状态
	CurrentUIType = EGameUIType::Game;

	//设置缩放状态为无
	MiniMapSizeMode = EMiniMapSizeMode::None;
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

	//绑定ESC键事件并且设置当暂停游戏的时候依然可以运行,bExecuteWhenPaused=true的意思就是你按ESC键游戏暂停了，再次按ESC回到游戏
	InputComponent->BindAction("EscEvent", IE_Pressed, this, &ASlAiPlayerController::EscEvent).bExecuteWhenPaused = true;
	//绑定背包
	InputComponent->BindAction("PackageEvent", IE_Pressed, this, &ASlAiPlayerController::PackageEvent);
	//聊天室
	InputComponent->BindAction("ChatRoomEvent", IE_Pressed, this, &ASlAiPlayerController::ChatRoomEvent);

	//绑定缩放小地图事件
	InputComponent->BindAction("AddMapSize", IE_Pressed, this, &ASlAiPlayerController::AddMapSizeStart);
	InputComponent->BindAction("AddMapSize", IE_Released, this, &ASlAiPlayerController::AddMapSizeStop);
	InputComponent->BindAction("ReduceMapSize", IE_Pressed, this, &ASlAiPlayerController::ReduceMapSizeStart);
	InputComponent->BindAction("ReduceMapSize", IE_Released, this, &ASlAiPlayerController::ReduceMapSizeStop);
}

void ASlAiPlayerController::EscEvent()
{
	switch (CurrentUIType)
	{
	case EGameUIType::Game:
		//设置游戏暂停
		SetPause(true);
		//设置输入模式为GameAndUI
		SwitchInputMode(false);
		//更新界面
		ShowGameUI.ExecuteIfBound(CurrentUIType, EGameUIType::Pause);
		//更新当前UI
		CurrentUIType = EGameUIType::Pause;
		//锁定输入
		LockedInput(true);
		break;
	case EGameUIType::Pause:
	case EGameUIType::Package:
	case EGameUIType::ChatRoom:
		//解除暂停
		SetPause(false);
		//设置游戏模式为游戏
		SwitchInputMode(true);
		//更新界面
		ShowGameUI.ExecuteIfBound(CurrentUIType, EGameUIType::Game);
		//更新当前UI
		CurrentUIType = EGameUIType::Game;
		//解开输入
		LockedInput(false);
		break;
	}
}

void ASlAiPlayerController::PackageEvent()
{
	switch (CurrentUIType)
	{
	case EGameUIType::Game:
		SwitchInputMode(false);
		ShowGameUI.ExecuteIfBound(CurrentUIType, EGameUIType::Package);
		CurrentUIType = EGameUIType::Package;
		LockedInput(true);
		break;
	case EGameUIType::Package:
		SwitchInputMode(true);
		ShowGameUI.ExecuteIfBound(CurrentUIType, EGameUIType::Game);
		CurrentUIType = EGameUIType::Game;
		LockedInput(false);
		break;
	}
}

void ASlAiPlayerController::ChatRoomEvent()
{
	switch (CurrentUIType)
	{
	case EGameUIType::Game:
		SwitchInputMode(false);
		ShowGameUI.ExecuteIfBound(CurrentUIType, EGameUIType::ChatRoom);
		CurrentUIType = EGameUIType::ChatRoom;
		LockedInput(true);
		break;
	case EGameUIType::ChatRoom:
		SwitchInputMode(true);
		ShowGameUI.ExecuteIfBound(CurrentUIType, EGameUIType::Game);
		CurrentUIType = EGameUIType::Game;
		LockedInput(false);
		break;
	}
}

void ASlAiPlayerController::SwitchInputMode(bool IsGameOnly)
{
	//这里就是出不出现UI的鼠标跟其他输入模式，有UI则输入经过鼠标，无则直接传给玩家Player
	if (IsGameOnly)
	{
		//隐藏鼠标
		bShowMouseCursor = false;
		//设置输入模式为OnlyGame
		FInputModeGameOnly InputMode;
		InputMode.SetConsumeCaptureMouseDown(true);
		SetInputMode(InputMode);
	}
	else {
		//显示鼠标
		bShowMouseCursor = true;
		//设置输入模式为GameAndUI
		FInputModeGameAndUI InputMode;;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		InputMode.SetHideCursorDuringCapture(false);
		SetInputMode(InputMode);
	}
}

void ASlAiPlayerController::LockedInput(bool IsLocked)
{
	SPCharacter->IsInputLocked = IsLocked;
}

void ASlAiPlayerController::AddMapSizeStart()
{
	//如果操作被锁住，直接返回
	if (SPCharacter->IsInputLocked) return;
	//设置缩放状态为增加
	MiniMapSizeMode = EMiniMapSizeMode::Add;
}

void ASlAiPlayerController::AddMapSizeStop()
{
	//如果操作被锁住，直接返回
	if (SPCharacter->IsInputLocked) return;
	//设置缩放状态为无
	MiniMapSizeMode = EMiniMapSizeMode::None;
}

void ASlAiPlayerController::ReduceMapSizeStart()
{
	//如果操作被锁住，直接返回
	if (SPCharacter->IsInputLocked) return;
	//设置缩放状态为减少
	MiniMapSizeMode = EMiniMapSizeMode::Reduce;
}

void ASlAiPlayerController::ReduceMapSizeStop()
{
	//如果操作被锁住，直接返回
	if (SPCharacter->IsInputLocked) return;
	//设置缩放状态为无
	MiniMapSizeMode = EMiniMapSizeMode::None;
}

void ASlAiPlayerController::TickMiniMap()
{
	switch (MiniMapSizeMode)
	{
	case EMiniMapSizeMode::Add:
		UpdateMiniMapWidth.ExecuteIfBound(5);
		break;
	case EMiniMapSizeMode::Reduce:
		UpdateMiniMapWidth.ExecuteIfBound(-5);
		break;

	}
}

void ASlAiPlayerController::DeadTimeOut()
{
	//设置游戏暂停
	SetPause(true);
	//设置游戏模式为混合
	SwitchInputMode(false);
	//更新界面
	ShowGameUI.ExecuteIfBound(CurrentUIType, EGameUIType::Lose);
	//更新当前UI
	CurrentUIType = EGameUIType::Lose;
	//锁住输入
	LockedInput(true);
}

void ASlAiPlayerController::ChangeHandObject()
{
	//生成手持物品
	SPCharacter->ChangeHandObject(ASlAiHandObject::SpawnHandObject(SPState->GetCurrentHandObjectIndex()));
}

void ASlAiPlayerController::PlayerDead()
{
	//转换到第三视角
	SPCharacter->ChangeView(EGameViewMode::Third);
	//告诉角色播放死亡动画,获得死亡时间
	float DeadDuration = SPCharacter->PlayDeadAnim();
	//锁住输入
	LockedInput(true);
	//添加事件委托
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &ASlAiPlayerController::DeadTimeOut);
	//延时跳转UI
	GetWorld()->GetTimerManager().SetTimer(DeadHandle, TimerDelegate, DeadDuration, false);
}

void ASlAiPlayerController::ChangeView()
{
	//如果操作被锁住，直接返回
	if (SPCharacter->IsInputLocked) return;

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
	//如果操作被锁住，直接返回
	if (SPCharacter->IsInputLocked) return;

	IsLeftButtonDown = true;
	SPCharacter->UpperType = LeftUpperType;
}

void ASlAiPlayerController::LeftEventStop()
{
	//如果操作被锁住，直接返回
	if (SPCharacter->IsInputLocked) return;

	IsLeftButtonDown = false;
	SPCharacter->UpperType = EUpperBody::None;
}

void ASlAiPlayerController::RightEventStart()
{
	//如果操作被锁住，直接返回
	if (SPCharacter->IsInputLocked) return;

	IsRightButtonDown = true;
	SPCharacter->UpperType = RightUpperType;
}

void ASlAiPlayerController::RightEventStop()
{
	//如果操作被锁住，直接返回
	if (SPCharacter->IsInputLocked) return;

	IsRightButtonDown = false;
	SPCharacter->UpperType = EUpperBody::None;
}

void ASlAiPlayerController::ScrollUpEvent()
{
	//如果操作被锁住，直接返回
	if (SPCharacter->IsInputLocked) return;

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
	//如果操作被锁住，直接返回
	if (SPCharacter->IsInputLocked) return;

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
		//画出射线
		//DrawRayLine(TraceStart, TraceEnd, 5.f);
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
	if (Cast<ASlAiEnemyCharacter>(RayActor))
	{
		IsDetected = true;
		SPState->RayInfoText = Cast<ASlAiEnemyCharacter>(RayActor)->GetInfoText();
	}
	//如果什么都没有检测到就设置信息为无
	if (!IsDetected)
	{
		SPState->RayInfoText = FText();
	}
}

void ASlAiPlayerController::StateMachine()
{
	//普通模式
	ChangePreUpperType(EUpperBody::None);
	if (!Cast<ASlAiResourceObject>(RayActor) && !Cast<ASlAiPickupObject>(RayActor) && !Cast<ASlAiEnemyCharacter>(RayActor))
	{
		//准星显示未锁定
		UpdatePointer.ExecuteIfBound(false, 1.f);
	}
	//如果检测到敌人
	if (Cast<ASlAiEnemyCharacter>(RayActor))
	{
		//准星锁定模式
		UpdatePointer.ExecuteIfBound(false, 0.f);
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
		if (IsRightButtonDown&&SPCharacter->IsPackageFree(Cast<ASlAiPickupObject>(RayActor)->ObjectIndex)) {
			//把物品捡起来
			SPCharacter->AddPackageObject(Cast<ASlAiPickupObject>(RayActor)->TakePickup());
		}
	}
}

