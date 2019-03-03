// Fill out your copyright notice in the Description page of Project Settings.

#include "SSlAiMenuWidget.h"
#include "SlateOptMacros.h"
#include "SlAiStyle.h"
#include "SlAiMenuWidgetStyle.h"
#include "SBox.h"
#include "SImage.h"
#include "STextBlock.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiMenuWidget::Construct(const FArguments& InArgs)
{
	//»ñÈ¡±à¼­Æ÷µÄMenuStyle
	MenuStyle = &SlAiStyle::Get().GetWidgetStyle < FSlAiMenuStyle > ("BPSlAiMenuStyle");

	ChildSlot
	[
		SAssignNew(RootSizeBox,SBox)
		[
			SNew(SOverlay)
	+SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).Padding(FMargin(0.f, 50.f, 0.f, 0.f))
		[
			SNew(SImage).Image(&MenuStyle->MenuBackgroundBrush)
		]
	+SOverlay::Slot().HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(FMargin(0.f,25.f,0.f,0.f))
		[
			SNew(SImage).Image(&MenuStyle->LeftIconBrush)
		]
	+SOverlay::Slot().HAlign(HAlign_Right).VAlign(VAlign_Center).Padding(FMargin(0.f, 25.f, 0.f, 0.f))
		[
			SNew(SImage).Image(&MenuStyle->RightIconBrush)
		]
	+SOverlay::Slot().HAlign(HAlign_Center).VAlign(VAlign_Top)
		[
			SNew(SBox).WidthOverride(400.f).HeightOverride(100.f)
			[
				SNew(SBorder).BorderImage(&MenuStyle->TitleBorderBrush).HAlign(HAlign_Center).VAlign(VAlign_Center)
				[
					SAssignNew(TitleText, STextBlock)
					.Font(SlAiStyle::Get().GetFontStyle("MenuItemFont"))
					.Text(FText::FromString("I am 11"))
					//.Text(NSLOCTEXT("SlAiMenu", "Menu", "Menu"))
				]
			]
		]

		]
	];
	
	RootSizeBox->SetWidthOverride(600.f);
	RootSizeBox->SetHeightOverride(510.f);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
