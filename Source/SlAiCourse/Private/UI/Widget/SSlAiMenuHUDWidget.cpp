// Fill out your copyright notice in the Description page of Project Settings.

#include "SSlAiMenuHUDWidget.h"
#include "SlateOptMacros.h"
#include "SButton.h"
#include "SImage.h"
#include "SlAiStyle.h"
#include "SlAiMenuWidgetStyle.h"
#include "Engine/Engine.h"
#include "SSlAiMenuWidget.h"
#include "SDPIScaler.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiMenuHUDWidget::Construct(const FArguments& InArgs)
{
	//获取编辑器的MenuStyle
	MenuStyle = &SlAiStyle::Get().GetWidgetStyle<FSlAiMenuStyle>("BPSlAiMenuStyle");
	//绑定缩放规则方法
	UIScaler.Bind(this, &SSlAiMenuHUDWidget::GetUIScaler);
	// 层级
	ChildSlot
		[
			SNew(SDPIScaler).DPIScale(UIScaler)
		[
			SNew(SOverlay)
			+SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill)
		[
			SNew(SImage).Image(&MenuStyle->MenuHUDBackgroundBrush)
		]
			+ SOverlay::Slot().HAlign(HAlign_Center).VAlign(VAlign_Center)
		[
			SAssignNew(MenuWidget, SSlAiMenuWidget)
		]

		]
		];
	
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

float SSlAiMenuHUDWidget::GetUIScaler() const
{
	return GetViewportSize().Y / 1080.f;
}

FVector2D SSlAiMenuHUDWidget::GetViewportSize() const
{
	FVector2D Result(1920, 1080);
	if (GEngine&&GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(Result);
	}
	return Result;
}