// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiPlayerController.h"
#include "SlAiPlayerCharacter.h"



ASlAiPlayerController::ASlAiPlayerController()
{
	//允许每帧运行
	PrimaryActorTick.bCanEverTick = true;
}

void ASlAiPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ASlAiPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//获取角色与状态
	if (!SPCharacter) SPCharacter = Cast<ASlAiPlayerCharacter>(GetCharacter());
	
	//设置鼠标不显示
	bShowMouseCursor = false;
	//设置输入模式
	FInputModeGameOnly InputMode;
	InputMode.SetConsumeCaptureMouseDown(true);
	SetInputMode(InputMode);

	//设置预动作
	LeftUpperType = EUpperBody::Punch;
	RightUpperType = EUpperBody::PickUp;
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
	SPCharacter->UpperType = LeftUpperType;
}

void ASlAiPlayerController::LeftEventStop()
{
	SPCharacter->UpperType = EUpperBody::None;
}

void ASlAiPlayerController::RightEventStart()
{
	SPCharacter->UpperType = RightUpperType;
}

void ASlAiPlayerController::RightEventStop()
{
	SPCharacter->UpperType = EUpperBody::None;
}