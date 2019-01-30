// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiMenuController.h"




ASlAiMenuController::ASlAiMenuController()
{
	bShowMouseCursor = true;
}

void ASlAiMenuController::BeginPlay()
{
	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);
}
