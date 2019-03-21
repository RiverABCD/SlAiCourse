// Fill out your copyright notice in the Description page of Project Settings.

#include "SSlAiMenuItemWidget.h"
#include "SlateOptMacros.h"
#include "SlAiStyle.h"
#include "SlAiMenuWidgetStyle.h"
#include "SBox.h"
#include "SImage.h"
#include "STextBlock.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiMenuItemWidget::Construct(const FArguments& InArgs)
{
	//获取编辑器的MenuStyle
	MenuStyle = &SlAiStyle::Get().GetWidgetStyle < FSlAiMenuStyle >("BPSlAiMenuStyle");

	OnClicked = InArgs._OnClicked;
	ItemType = InArgs._ItemType.Get();
	
	ChildSlot
	[
		SNew(SBox).WidthOverride(500.f).HeightOverride(100.f)
		[
			SNew(SOverlay)
			+ SOverlay::Slot().VAlign(VAlign_Fill).HAlign(HAlign_Fill)
			[
				SNew(SImage).Image(&MenuStyle->MenuItemBrush)
				.ColorAndOpacity(this, &SSlAiMenuItemWidget::GetTintColor)
			]
			+ SOverlay::Slot().HAlign(HAlign_Center).VAlign(VAlign_Center)
			[
				SNew(STextBlock).Text(InArgs._ItemText).Font(MenuStyle->Font_60)
			]


		]
	];
	//初始化
	IsMouseButtonDown = false;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FReply SSlAiMenuItemWidget::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	IsMouseButtonDown = true;
	return FReply::Handled();
}

FReply SSlAiMenuItemWidget::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	//如果按钮按下了并且OnClicked委托绑定有方法那就执行
	if (IsMouseButtonDown)
	{
		IsMouseButtonDown = false;
		OnClicked.ExecuteIfBound(ItemType);
	}
	return FReply::Handled();
}

void SSlAiMenuItemWidget::OnMouseLeave(const FPointerEvent & MouseEvent)
{
	IsMouseButtonDown = false;
}

FSlateColor SSlAiMenuItemWidget::GetTintColor() const
{
	if (IsMouseButtonDown) return FLinearColor(1.f, 0.1f, 0.1f, 0.5f);
	return FLinearColor(1.f, 1.f, 1.f, 1.f);
}
