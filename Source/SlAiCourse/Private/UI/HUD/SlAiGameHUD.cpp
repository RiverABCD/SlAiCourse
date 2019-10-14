// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiGameHUD.h"
#include "Engine/Engine.h"
#include "SlateBasics.h"
#include "Kismet/GameplayStatics.h"

#include "SSlAiGameHUDWidget.h"
#include "SSlAiShortcutWidget.h"
#include "SSlAiRayInfoWidget.h"
#include "SSlAiPointerWidget.h"
#include "SSlAiMiniMapWidget.h"

#include "SlAiPlayerController.h"
#include "SlAiPlayerState.h"
#include "SlAiGameMode.h"
#include "Engine/GameViewportClient.h"
#include "SSlAiPlayerStateWidget.h"
#include "SSlAiPackageWidget.h"



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
	//绑定注册快捷栏容器
	GameHUDWidget->ShortcutWidget->RegisterShortcutContainer.BindUObject(GM->SPState, &ASlAiPlayerState::RegisterShortcutContainer);
	//绑定射线信息文本事件
	GameHUDWidget->RayInfoWidget->RegisterRayInfoEvent.BindUObject(GM->SPState, &ASlAiPlayerState::RegisterRayInfoEvent);
	//绑定修改准星委托(BindRaw绑定的继承纯C++类，而BindUObject则绑定的是继承 自UObject类)
	GM->SPController->UpdatePointer.BindRaw(GameHUDWidget->PointerWidget.Get(), &SSlAiPointerWidget::UpdatePointer);
	//绑定更新玩家状态的委托
	GM->SPState->UpdateStateWidget.BindRaw(GameHUDWidget->PlayerStateWidget.Get(), &SSlAiPlayerStateWidget::UpdateStateWidget);
	//绑定显示UI委托
	GM->SPController->ShowGameUI.BindRaw(GameHUDWidget.Get(), &SSlAiGameHUDWidget::ShowGameUI);
	//初始化背包管理器到背包组件
	GM->InitPackageManager.BindRaw(GameHUDWidget->PackageWidget.Get(), &SSlAiPackageWidget::InitPackageManager);
	//绑定注册小地图贴图委托
	GM->RegisterMiniMap.BindRaw(GameHUDWidget->MiniMapWidget.Get(), &SSlAiMiniMapWidget::RegisterMiniMap);
}
