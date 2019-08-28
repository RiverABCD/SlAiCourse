// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiGameHUD.h"
#include "Engine/Engine.h"
#include "SlateBasics.h"
#include "Kismet/GameplayStatics.h"

#include "SSlAiGameHUDWidget.h"
#include "SSlAiShortcutWidget.h"

#include "SlAiPlayerController.h"
#include "SlAiPlayerState.h"
#include "SlAiGameMode.h"


ASlAiGameHUD::ASlAiGameHUD()
{
	if (GEngine && GEngine->GameViewport)
	{
		SAssignNew(GameHUDWidget, SSlAiGameHUDWidget);
		GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(GameHUDWidget.ToSharedRef()));
	}
}

void ASlAiGameHUD::BeginPlay()
{
	Super::BeginPlay();
	//为什么不在构造函数中绑定Controller,Character，State：因为执行到构造时，世界中并没有实例化这些类
	GM = Cast<ASlAiGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GM) return;
	//先确保要调用的组件都已经实现
	GM->InitGamePlayModule();
	GameHUDWidget->ShortcutWidget->RegisterShortcutContainer.BindUObject(GM->SPState, &ASlAiPlayerState::RegisterShortcutContainer);
}
