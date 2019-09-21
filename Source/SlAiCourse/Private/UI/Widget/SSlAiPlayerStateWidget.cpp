// Fill out your copyright notice in the Description page of Project Settings.

#include "SSlAiPlayerStateWidget.h"
#include "SlateOptMacros.h"
#include "SlAiGameWidgetStyle.h"
#include "SlAiStyle.h"
#include "SBox.h"
#include "SOverlay.h"
#include "SImage.h"
#include "SConstraintCanvas.h"//相当于UMG的CanvasPanel
#include "SProgressBar.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiPlayerStateWidget::Construct(const FArguments& InArgs)
{
	//获取GameStyle
	GameStyle = &SlAiStyle::Get().GetWidgetStyle<FSlAiGameStyle>("BPSlAiGameStyle");
	
	ChildSlot
	[
		SNew(SBox).WidthOverride(744.f).HeightOverride(244.f)
		[
			SNew(SOverlay)
			//状态背景图片
			+ SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill)
			[
				SNew(SImage).Image(&GameStyle->PlayerStateBGBrush)
			]
			//添加进度条的CanvasPanel
			+ SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill)
			[
				SNew(SConstraintCanvas)
				//血条
				+ SConstraintCanvas::Slot().Anchors(FAnchors(0.f))//设置锚点为左上角
				.Offset(FMargin(442.3f, 90.f, 418.f, 42.f))//锚点为左上角的时候就相当于设置位置和大小
				[
					SAssignNew(HPBar,SProgressBar)
					.BackgroundImage(&GameStyle->EmptyBrush)
					.FillImage(&GameStyle->HPBrush)
					.FillColorAndOpacity(FSlateColor(FLinearColor(1.f,1.f,1.f,1.f)))
					.Percent(1.f)
				]
				//饥饿度
				+SConstraintCanvas::Slot().Anchors(FAnchors(0.f)).Offset(FMargin(397.5f, 145.f, 317.f, 26.f))
				[
					SAssignNew(HungerBar,SProgressBar)
					.BackgroundImage(&GameStyle->EmptyBrush)
					.FillImage(&GameStyle->HungerBrush)
					.FillColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f, 1.f, 1.f)))
					.Percent(1.f)
				]
			]
			//添加人物头像背景和头像的Overlay
			+ SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).Padding(FMargin(0.f, 0.f, 500.f, 0.f))
			[
				SNew(SOverlay)
				+ SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill)
				[
					SNew(SImage).Image(&GameStyle->PlayerHeadBGBrush)
				]
				+ SOverlay::Slot().HAlign(HAlign_Center).VAlign(VAlign_Center)
				[
					SNew(SImage).Image(&GameStyle->PlayerHeadBrush)
				]
			]
		]
	];
	
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSlAiPlayerStateWidget::UpdateStateWidget(float HPValue, float HungerValue)
{
	if (HPValue > 0) HPBar->SetPercent(FMath::Clamp<float>(HPValue, 0.f, 1.f));
	if (HungerValue > 0) HungerBar->SetPercent(FMath::Clamp<float>(HungerValue, 0.f, 1.f));
}
