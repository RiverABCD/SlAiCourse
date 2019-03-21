// Fill out your copyright notice in the Description page of Project Settings.

#include "SSlAiMenuWidget.h"
#include "SlateOptMacros.h"
#include "SlAiStyle.h"
#include "SlAiMenuWidgetStyle.h"
#include "SBox.h"
#include "SImage.h"
#include "STextBlock.h"
#include "SSlAiMenuItemWidget.h"
#include "SBoxPanel.h"
#include "Internationalization.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiMenuWidget::Construct(const FArguments& InArgs)
{
	//��ȡ�༭����MenuStyle
	MenuStyle = &SlAiStyle::Get().GetWidgetStyle < FSlAiMenuStyle > ("BPSlAiMenuStyle");

	FInternationalization::Get().SetCurrentCulture(TEXT("en"));
	//FInternationalization::Get().SetCurrentCulture(TEXT("zh"));

	ChildSlot
	[
		SAssignNew(RootSizeBox,SBox)
		[
			SNew(SOverlay)
			+SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).Padding(FMargin(0.f, 50.f, 0.f, 0.f))
			[
				SNew(SImage).Image(&MenuStyle->MenuBackgroundBrush)//UMG����ͼ
			]
			+SOverlay::Slot().HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(FMargin(0.f,25.f,0.f,0.f))
			[
				SNew(SImage).Image(&MenuStyle->LeftIconBrush)//UMG��߿�
			]
			+SOverlay::Slot().HAlign(HAlign_Right).VAlign(VAlign_Center).Padding(FMargin(0.f, 25.f, 0.f, 0.f))
			[
				SNew(SImage).Image(&MenuStyle->RightIconBrush)//UMG�ұ߿�
			]
			+SOverlay::Slot().HAlign(HAlign_Center).VAlign(VAlign_Top)
			[
				SNew(SBox).WidthOverride(400.f).HeightOverride(100.f)
				[
					SNew(SBorder).BorderImage(&MenuStyle->TitleBorderBrush).HAlign(HAlign_Center).VAlign(VAlign_Center)
					[
						SAssignNew(TitleText, STextBlock)//����
						.Font(SlAiStyle::Get().GetFontStyle("MenuItemFont"))
						//.Text(FText::FromString("I am 12"))
						.Text(NSLOCTEXT("SlAiMenu", "Menu", "Menu"))//���ֱ��ػ�
					]
				]
			]
			+SOverlay::Slot().HAlign(HAlign_Center).VAlign(VAlign_Top).Padding(FMargin(0.f,130.f,0.f,0.f))
			[
				SAssignNew(ContentBox,SVerticalBox)
			]
		]
	];
	
	RootSizeBox->SetWidthOverride(600.f);
	RootSizeBox->SetHeightOverride(510.f);

	ContentBox->AddSlot()
		[
			SNew(SSlAiMenuItemWidget)
			.ItemText(NSLOCTEXT("SlAiMenu", "StartGame", "StartGame"))
		.ItemType(EMenuItem::StartGame)
		.OnClicked(this, &SSlAiMenuWidget::MenuItemOnClicked)
		];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSlAiMenuWidget::MenuItemOnClicked(EMenuItem::Type ItemType)
{
	TitleText->SetText(NSLOCTEXT("SlAiMenu", "StartGame", "StartGame"));
}
