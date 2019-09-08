// Fill out your copyright notice in the Description page of Project Settings.

#include "SSlAiRayInfoWidget.h"
#include "SlateOptMacros.h"
#include "SlAiGameWidgetStyle.h"
#include "SlAiStyle.h"

#include "SBorder.h"
#include "SBox.h"
#include "STextBlock.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiRayInfoWidget::Construct(const FArguments& InArgs)
{
	//获取GameStyle
	GameStyle = &SlAiStyle::Get().GetWidgetStyle<FSlAiGameStyle>("BPSlAiGameStyle");

	ChildSlot
		[
			SNew(SBox).WidthOverride(400.f).HeightOverride(100.f)
			[
				SNew(SBorder).BorderImage(&GameStyle->RayInfoBrush).HAlign(HAlign_Center).VAlign(VAlign_Center)
				[
					SAssignNew(RayInfoTextBlock, STextBlock).Font(GameStyle->Font_Outline_50)
					.ColorAndOpacity(GameStyle->FontColor_Black)
				]
			]
		];

}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSlAiRayInfoWidget::Tick(const FGeometry & AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	//第一帧的时候进行初始化
	if (!IsInitRayInfoEvent)
	{
		RegisterRayInfoEvent.ExecuteIfBound(RayInfoTextBlock);
		IsInitRayInfoEvent = true;
	}
}