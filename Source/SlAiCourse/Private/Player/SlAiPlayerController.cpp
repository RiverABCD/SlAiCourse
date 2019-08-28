// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiPlayerController.h"




ASlAiPlayerController::ASlAiPlayerController()
{
	//����ÿ֡����
	PrimaryActorTick.bCanEverTick = true;
}

void ASlAiPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ASlAiPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//��ȡ��ɫ��״̬
	if (!SPCharacter) SPCharacter = Cast<ASlAiPlayerCharacter>(GetCharacter());
	if (!SPState) SPState = Cast<ASlAiPlayerState>(PlayerState);
	
	//������겻��ʾ
	bShowMouseCursor = false;
	//��������ģʽ
	FInputModeGameOnly InputMode;
	InputMode.SetConsumeCaptureMouseDown(true);
	SetInputMode(InputMode);

	//����Ԥ����
	LeftUpperType = EUpperBody::Punch;
	RightUpperType = EUpperBody::PickUp;

	IsLeftButtonDown = false;
	IsRightButtonDown = false;
}

void ASlAiPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//���ӽ��л�
	InputComponent->BindAction("ChangeView", IE_Pressed, this, &ASlAiPlayerController::ChangeView);
	//����갴���¼�
	InputComponent->BindAction("LeftEvent", IE_Pressed, this, &ASlAiPlayerController::LeftEventStart);
	InputComponent->BindAction("LeftEvent", IE_Released, this, &ASlAiPlayerController::LeftEventStop);
	InputComponent->BindAction("RightEvent", IE_Pressed, this, &ASlAiPlayerController::RightEventStart);
	InputComponent->BindAction("RightEvent", IE_Released, this, &ASlAiPlayerController::RightEventStop);
	//���������¼�
	InputComponent->BindAction("ScrollUp", IE_Pressed, this, &ASlAiPlayerController::ScrollUpEvent);
	InputComponent->BindAction("ScrollDown", IE_Pressed, this, &ASlAiPlayerController::ScrollDownEvent);
}

void ASlAiPlayerController::ChangeView()
{
	//����������л��ӽǣ�ֱ�ӷ���
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
	//����������л���ֱ�ӷ���
	if (!SPCharacter->IsAllowSwitch) return;

	//���������ڰ�������׼��ת
	if (IsLeftButtonDown || IsRightButtonDown) return;
	//����״̬���л����������
	SPState->ChooseShortcut(true);

}

void ASlAiPlayerController::ScrollDownEvent()
{
	//����������л���ֱ�ӷ���
	if (!SPCharacter->IsAllowSwitch) return;

	//���������ڰ�������׼��ת
	if (IsLeftButtonDown || IsRightButtonDown) return;
	//����״̬���л����������
	SPState->ChooseShortcut(false);
}
