// Fill out your copyright notice in the Description page of Project Settings.

#include "SSlAiPackageWidget.h"
#include "SlateOptMacros.h"
#include "SlAiStyle.h"
#include "SlAiGameWidgetStyle.h"

#include "SSlAiContainerBaseWidget.h"
#include "SOverlay.h"
#include "SBox.h"
#include "SImage.h"
#include "SUniformGridPanel.h"

#include "Engine/GameEngine.h"
#include "Engine/Engine.h"
#include "SlAiHelper.h"

#include "SlAiPackageManager.h"
#include "SlAiDataHandle.h"
#include "Engine/GameViewportClient.h"

#include "SlAiPackageManager.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiPackageWidget::Construct(const FArguments& InArgs)
{
	//获取GameStyle
	GameStyle = &SlAiStyle::Get().GetWidgetStyle<FSlAiGameStyle>("BPSlAiGameStyle");

	//获取DPIScaler
	UIScaler = InArgs._UIScaler;

	ChildSlot
		[
			SNew(SOverlay)
			//背包
			+ SOverlay::Slot().HAlign(HAlign_Right).VAlign(VAlign_Center).Padding(FMargin(0.f,0.f,50.f,0.f))
			[
				SNew(SBox).WidthOverride(800.f).HeightOverride(800.f)
				[
					SNew(SOverlay)
					//背景图
					+ SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill)
					[
						SNew(SImage).Image(&GameStyle->PackageBGBrush)
					]
					//底部快捷栏
					+ SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).Padding(FMargin(40.f,680.f,40.f,40.f))
					[
						SAssignNew(ShortcutGrid,SUniformGridPanel)
					]
					//背包主体
					+ SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).Padding(FMargin(40.f, 320.f, 40.f, 160.f))
					[
						SAssignNew(PackageGrid,SUniformGridPanel)
					]
					//合成表输入框
					+ SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).Padding(FMargin(80.f, 40.f, 480.f, 520.f))
					[
						SAssignNew(CompoundGrid,SUniformGridPanel)
					]
					//合成表输出框
					+ SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).Padding(FMargin(560.f, 120.f, 160.f, 600.f))
					[
						SAssignNew(OutputBorder,SBorder)
					]
					//合成小箭头
					+ SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).Padding(FMargin(400.f, 120.f, 320.f, 600.f))
					[
						SNew(SImage).Image(&GameStyle->CompoundArrowBrush)
					]
				]
			]
		];
	MousePosition = FVector2D(0.f, 0.f);
	IsInitPackageMana = false;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION


void SSlAiPackageWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	//如果背包显示并且世界存在,实时更新鼠标位置
	if (GetVisibility() == EVisibility::Visible&&GEngine)
	{
		GEngine->GameViewport->GetMousePosition(MousePosition);
		//SlAiHelper::Debug(FString("AbsoMousePos:") + MousePosition.ToString(), 0.f);
		MousePosition = MousePosition / UIScaler.Get();
		//SlAiHelper::Debug(FString("RelaMousePos:") + MousePosition.ToString(), 0.f);
	}
	//如果背包管理器已经初始化
	if (IsInitPackageMana)
	{
		//实时更新容器悬停显示
		SlAiPackageManager::Get()->UpdateHovered(MousePosition, AllottedGeometry);
	}
}

void SSlAiPackageWidget::InitPackageManager()
{
	//初始化快捷栏
	for (int i = 0; i < 9; ++i)
	{
		//创建容器实例
		TSharedPtr<SSlAiContainerBaseWidget> NewContainer = SSlAiContainerBaseWidget::CreateContainer(EContainerType::Shortcut, i);
		//将容器添加到UI
		ShortcutGrid->AddSlot(i, 0)[NewContainer->AsShared()];
		//注册容器到背包管理器
		SlAiPackageManager::Get()->InsertContainer(NewContainer, EContainerType::Shortcut);
	}
	//初始化背包主体
	for (int i = 0; i < 36; ++i) {
		TSharedPtr<SSlAiContainerBaseWidget> NewContainer = SSlAiContainerBaseWidget::CreateContainer(EContainerType::Normal, i);
		PackageGrid->AddSlot(i % 9, i / 9)[NewContainer->AsShared()];
		SlAiPackageManager::Get()->InsertContainer(NewContainer, EContainerType::Normal);
	}
	//初始化合成台
	for (int i = 0; i < 9; ++i) {
		TSharedPtr<SSlAiContainerBaseWidget> NewContainer = SSlAiContainerBaseWidget::CreateContainer(EContainerType::Input, i);
		CompoundGrid->AddSlot(i % 3, i / 3)[NewContainer->AsShared()];
		SlAiPackageManager::Get()->InsertContainer(NewContainer, EContainerType::Input);
	}
	//初始化输出容器
	TSharedPtr<SSlAiContainerBaseWidget> NewContainer = SSlAiContainerBaseWidget::CreateContainer(EContainerType::Output, 1);
	OutputBorder->SetContent(NewContainer->AsShared());
	SlAiPackageManager::Get()->InsertContainer(NewContainer, EContainerType::Output);

	//设置已经初始化背包管理器
	IsInitPackageMana = true;
}

