// Fill out your copyright notice in the Description page of Project Settings.

#include "SSlAiGameHUDWidget.h"
#include "SlateOptMacros.h"
#include "Engine/Engine.h"
#include "SDPIScaler.h"
#include "SOverlay.h"
#include "SBorder.h"

#include "SSlAiShortcutWidget.h"
#include "Engine/GameViewportClient.h"
#include "SSlAiRayInfoWidget.h"
#include "SSlAiPointerWidget.h"
#include "SSlAiPlayerStateWidget.h"

#include "SSlAiGameMenuWidget.h"
#include "SSlAiChatRoomWidget.h"
#include "SSlAiPackageWidget.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiGameHUDWidget::Construct(const FArguments& InArgs)
{
	UIScaler.Bind(this, &SSlAiGameHUDWidget::GetUIScaler);
	ChildSlot
	[
		SNew(SDPIScaler).DPIScale(UIScaler)
		[
			SNew(SOverlay)
			//快捷栏
			+ SOverlay::Slot().HAlign(HAlign_Center).VAlign(VAlign_Bottom)
			[
				SAssignNew(ShortcutWidget,SSlAiShortcutWidget)
			]
			//射线信息
			+ SOverlay::Slot().HAlign(HAlign_Center).VAlign(VAlign_Top)
			[
				SAssignNew(RayInfoWidget,SSlAiRayInfoWidget)
			]
			//准星
			+ SOverlay::Slot().HAlign(HAlign_Center).VAlign(VAlign_Center)
			[
				SAssignNew(PointerWidget,SSlAiPointerWidget)
			]
			//玩家状态
			+ SOverlay::Slot().HAlign(HAlign_Left).VAlign(VAlign_Top)
			[
				SAssignNew(PlayerStateWidget,SSlAiPlayerStateWidget)
			]
			//黑色遮罩，放在事件界面和游戏UI中间
			+SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill)
			[
					SAssignNew(BlackShade, SBorder)
					//设置为黑色透明
					.ColorAndOpacity(TAttribute<FLinearColor>(FLinearColor(0.2f, 0.2f, 0.2f, 0.5f)))
					//开始时设置不显示
					.Visibility(EVisibility::Hidden)
					[
						SNew(SImage)
					]
			]
			//GameMenu
			+ SOverlay::Slot().HAlign(HAlign_Center).VAlign(VAlign_Center)
			[
				SAssignNew(GameMenuWidget, SSlAiGameMenuWidget).Visibility(EVisibility::Hidden)
			]

			//chatRoom
			+ SOverlay::Slot().HAlign(HAlign_Left).VAlign(VAlign_Bottom)
			[
				SAssignNew(ChatRoomWidget, SSlAiChatRoomWidget).Visibility(EVisibility::Hidden)
			]
			//Package
			+SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill)
			[
				SAssignNew(PackageWidget, SSlAiPackageWidget)
				//设置DPI
				.UIScaler(UIScaler)//传至SlAiPackageWidget
				.Visibility(EVisibility::Hidden)
			]
		]
	];
	
	InitUIMap();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

float SSlAiGameHUDWidget::GetUIScaler() const
{
	return GetViewportSize().Y/1080.f;
}

void SSlAiGameHUDWidget::ShowGameUI(EGameUIType::Type PreUI, EGameUIType::Type NextUI)
{
	//如果前一模式是Game,说明要显示黑板
	if (PreUI == EGameUIType::Game)
	{
		BlackShade->SetVisibility(EVisibility::Visible);
	}
	else {
		//隐藏当前正在显示的UI
		UIMap.Find(PreUI)->Get()->SetVisibility(EVisibility::Hidden);
	}
	//如果下一模式是Game,隐藏黑板
	if (NextUI == EGameUIType::Game)
	{
		BlackShade->SetVisibility(EVisibility::Hidden);
	}
	else {
		//显示现在状态对应的UI
		UIMap.Find(NextUI)->Get()->SetVisibility(EVisibility::Visible);
	}
}

FVector2D SSlAiGameHUDWidget::GetViewportSize() const
{
	FVector2D Result(1920.f, 1080.f);
	if (GEngine&&GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(Result);
	}
	return Result;
}

void SSlAiGameHUDWidget::InitUIMap()
{
	UIMap.Add(EGameUIType::Pause, GameMenuWidget);
	UIMap.Add(EGameUIType::Package, PackageWidget);
	UIMap.Add(EGameUIType::ChatRoom, ChatRoomWidget);
	UIMap.Add(EGameUIType::Lose, GameMenuWidget);

	//绑定委托

}
