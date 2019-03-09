// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiMenuController.h"




ASlAiMenuController::ASlAiMenuController()
{
	//显示鼠标
	bShowMouseCursor = true;
}

void ASlAiMenuController::BeginPlay()
{
	//设置鼠标显示模式
	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);
}
