// Fill out your copyright notice in the Description page of Project Settings.

#include "SSlAiShortcutWidget.h"
#include "SlateOptMacros.h"
#include "SlAiStyle.h"
#include "SlAiGameWidgetStyle.h"
#include "SlAiDataHandle.h"

#include "SBox.h"
#include "SOverlay.h"
#include "STextBlock.h"
#include "SUniformGridPanel.h"
#include "SBorder.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiShortcutWidget::Construct(const FArguments& InArgs)
{
	//获取GameStyle
	GameStyle = &SlAiStyle::Get().GetWidgetStyle<FSlAiGameStyle>("BPSlAiGameStyle");
	
	ChildSlot
	[
		SNew(SBox).WidthOverride(900.f).HeightOverride(160.f)
		[
			SNew(SOverlay)
			+SOverlay::Slot().HAlign(HAlign_Center).VAlign(VAlign_Top)
			[
				SAssignNew(ShortcutInfoTextBlock,STextBlock).Font(GameStyle->Font_40).ColorAndOpacity(GameStyle->FontColor_White)
			]
			+SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).Padding(FMargin(0.f,60.f,0.f,0.f))
			[
				SAssignNew(GridPanel,SUniformGridPanel)
			]
		]
	];
	
	//设置没有初始化容器
	IsInitializeContainer = false;

}

void SSlAiShortcutWidget::Tick(const FGeometry & AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	if (!IsInitializeContainer) {
		InitializeContainer();
		IsInitializeContainer = true;
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSlAiShortcutWidget::InitializeContainer()
{
	TArray<TSharedPtr<ShortcutContainer>> ContainerList;

	for (int i = 0; i < 9; i++)
	{
		//创建容器
		TSharedPtr<SBorder> ContainerBorder;
		TSharedPtr<SBorder> ObjectImage;
		TSharedPtr<STextBlock> ObjectNumText;

		SAssignNew(ContainerBorder,SBorder)
			.Padding(FMargin(10.f))
			[
				SAssignNew(ObjectImage,SBorder)
				.HAlign(HAlign_Right).VAlign(VAlign_Bottom)
				.Padding(FMargin(0.f,0.f,5.f,0.f))
				[
					SAssignNew(ObjectNumText,STextBlock)
					.Font(GameStyle->Font_Outline_20)
					.ColorAndOpacity(GameStyle->FontColor_Black)
				]
			];
		//将容器添加到网格
		GridPanel->AddSlot(i, 0)
			[
				ContainerBorder->AsShared()
			];
		//实例化一个容器结构体
		TSharedPtr<ShortcutContainer> Container = MakeShareable(new ShortcutContainer(ContainerBorder, ObjectImage, ObjectNumText, \
			&GameStyle->NormalContainerBrush, &GameStyle->ChoosedContainerBrush, &SlAiDataHandle::Get()->ObjectBrushList));
		
		if (i == 0) Container->SetChoosed(true);
		ContainerList.Add(Container);
	}

	//将实例化的结构体注册进PlayerState的容器数组
	RegisterShortcutContainer.ExecuteIfBound(&ContainerList, ShortcutInfoTextBlock);
}