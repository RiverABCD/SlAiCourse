// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiMenuController.h"




ASlAiMenuController::ASlAiMenuController()
{
	//��ʾ���
	bShowMouseCursor = true;
}

void ASlAiMenuController::BeginPlay()
{
	//���������ʾģʽ
	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);
}
