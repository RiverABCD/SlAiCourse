// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiPlayerController.h"
#include "SlAiHandObject.h"
#include "SlAiPlayerState.h"
#include "SlAiPlayerCharacter.h"


ASlAiPlayerController::ASlAiPlayerController()
{
	//允许每帧运行
	PrimaryActorTick.bCanEverTick = true;
}

void ASlAiPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//临时代码
	ChangePreUpperType(EUpperBody::None);
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
