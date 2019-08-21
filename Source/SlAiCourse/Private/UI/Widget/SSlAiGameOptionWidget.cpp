// Fill out your copyright notice in the Description page of Project Settings.

#include "SSlAiGameOptionWidget.h"
#include "SlateOptMacros.h"
#include "SlAiStyle.h"
#include "SlAiMenuWidgetStyle.h"
#include "SBox.h"
#include "SOverlay.h"
#include "SBorder.h"
#include "SBoxPanel.h"
#include "STextBlock.h"
#include "SCheckBox.h"
#include "SSlider.h"

#include "SlAiDataHandle.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiGameOptionWidget::Construct(const FArguments& InArgs)
{
	//获取编辑器的MenuStyle
	MenuStyle = &SlAiStyle::Get().GetWidgetStyle < FSlAiMenuStyle >("BPSlAiMenuStyle");
	
	//获取委托
	ChangeCulture = InArgs._ChangeCulture;
	ChangeVolume = InArgs._ChangeVolume;

	ChildSlot
	[
		SNew(SBox).WidthOverride(500.f).HeightOverride(300.f)
		[
			SNew(SOverlay)
			+SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill)
			[
				SNew(SImage).Image(&MenuStyle->GameOptionBGBrush)
			]
			+SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).Padding(FMargin(50.f))
			[
				SNew(SVerticalBox)
				//第一行
				+SVerticalBox::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).FillHeight(1.f)
				[
					SNew(SHorizontalBox)
					+SHorizontalBox::Slot().HAlign(HAlign_Center).VAlign(VAlign_Center).FillWidth(1.f)
					[
						SAssignNew(ZhCheckBox, SCheckBox).OnCheckStateChanged(this, &SSlAiGameOptionWidget::ZhCheckBoxStateChanged)
						[
							SNew(STextBlock).Font(MenuStyle->Font_40).ColorAndOpacity(MenuStyle->FontColor_Black).Text(NSLOCTEXT("SlAiMenu", "Chinese", "Chinese"))
						]
					]
					+SHorizontalBox::Slot().HAlign(HAlign_Center).VAlign(VAlign_Center).FillWidth(1.f)
					[
						SAssignNew(EnCheckBox, SCheckBox).OnCheckStateChanged(this, &SSlAiGameOptionWidget::EnCheckBoxStateChanged)
						[
							SNew(STextBlock).Font(MenuStyle->Font_40).ColorAndOpacity(MenuStyle->FontColor_Black).Text(NSLOCTEXT("SlAiMenu", "English", "English"))
						]
					]
				]
				//第二行
				+ SVerticalBox::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).FillHeight(1.f)
				[
					SNew(SOverlay)
					+ SOverlay::Slot().HAlign(HAlign_Left).VAlign(VAlign_Center)
					[
						SNew(STextBlock).Font(MenuStyle->Font_40).ColorAndOpacity(MenuStyle->FontColor_Black).Text(NSLOCTEXT("SlAiMenu", "Music", "Music"))
					]
					+ SOverlay::Slot().HAlign(HAlign_Center).VAlign(VAlign_Center)
					[
						SNew(SBox).WidthOverride(240.f)
						[
							SNew(SOverlay)
							+ SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Center).Padding(FMargin(30.f, 0.f))
							[
								SNew(SImage).Image(&MenuStyle->SliderBarBrush)
							]
							+ SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Center)   
							[
								SAssignNew(MuSlider, SSlider).Style(&MenuStyle->SliderStyle).OnValueChanged(this, &SSlAiGameOptionWidget::MusicSliderChanged)
							]
						]
				   ]
					+ SOverlay::Slot().HAlign(HAlign_Right).VAlign(VAlign_Center)
					[
						SAssignNew(MuTextBlock, STextBlock).Font(MenuStyle->Font_40).ColorAndOpacity(MenuStyle->FontColor_Black)
					]
				]

			//第三行
				+ SVerticalBox::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).FillHeight(1.f)
				[
					SNew(SOverlay)
					+ SOverlay::Slot().HAlign(HAlign_Left).VAlign(VAlign_Center)
					[
					SNew(STextBlock).Font(MenuStyle->Font_40).ColorAndOpacity(MenuStyle->FontColor_Black).Text(NSLOCTEXT("SlAiMenu", "Sound", "Sound"))
					]
					+ SOverlay::Slot().HAlign(HAlign_Center).VAlign(VAlign_Center)
					[
						SNew(SBox).WidthOverride(240.f)
						[
							SNew(SOverlay)
							+ SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Center).Padding(FMargin(30.f, 0.f))
							[
								SNew(SImage).Image(&MenuStyle->SliderBarBrush)
							]
							+ SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Center)
							[
								SAssignNew(SoSlider, SSlider).Style(&MenuStyle->SliderStyle).OnValueChanged(this, &SSlAiGameOptionWidget::SoundSliderChanged)
							]

					    ]
					]
					+ SOverlay::Slot().HAlign(HAlign_Right).VAlign(VAlign_Center)
					[
						SAssignNew(SoTextBlock, STextBlock).Font(MenuStyle->Font_40).ColorAndOpacity(MenuStyle->FontColor_Black)
					]
				]
			]
		]
	];
	
	StyleInitialize();
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSlAiGameOptionWidget::StyleInitialize()
{
	////设置ZhCheckBox样式
	ZhCheckBox->SetUncheckedImage(&MenuStyle->UnCheckedBoxBrush);
	ZhCheckBox->SetUncheckedHoveredImage(&MenuStyle->UnCheckedBoxBrush);
	ZhCheckBox->SetUncheckedPressedImage(&MenuStyle->UnCheckedBoxBrush);
	ZhCheckBox->SetCheckedImage(&MenuStyle->CheckedBoxBrush);
	ZhCheckBox->SetCheckedHoveredImage(&MenuStyle->CheckedBoxBrush);
	ZhCheckBox->SetCheckedPressedImage(&MenuStyle->CheckedBoxBrush);

	//设置EnCheckBox样式
	EnCheckBox->SetUncheckedImage(&MenuStyle->UnCheckedBoxBrush);
	EnCheckBox->SetUncheckedHoveredImage(&MenuStyle->UnCheckedBoxBrush);
	EnCheckBox->SetUncheckedPressedImage(&MenuStyle->UnCheckedBoxBrush);
	EnCheckBox->SetCheckedImage(&MenuStyle->CheckedBoxBrush);
	EnCheckBox->SetCheckedHoveredImage(&MenuStyle->CheckedBoxBrush);
	EnCheckBox->SetCheckedPressedImage(&MenuStyle->CheckedBoxBrush);

	switch(SlAiDataHandle::Get()->CurrentCulture) 
	{
	case ECultureTeam::EN:
		EnCheckBox->SetIsChecked(ECheckBoxState::Checked);
		ZhCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
		break;
	case ECultureTeam::ZH:
		EnCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
		ZhCheckBox->SetIsChecked(ECheckBoxState::Checked);
		break;
	}

	MuSlider->SetValue(SlAiDataHandle::Get()->MusicVolume);
	SoSlider->SetValue(SlAiDataHandle::Get()->SoundVolume);

	MuTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(SlAiDataHandle::Get()->MusicVolume*100))+FString("%")));
	SoTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(SlAiDataHandle::Get()->SoundVolume*100))+FString("%")));

}

void SSlAiGameOptionWidget::ZhCheckBoxStateChanged(ECheckBoxState NewState)
{
	//设置被选中的框
	EnCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
	ZhCheckBox->SetIsChecked(ECheckBoxState::Checked);
	//告诉数据控制类转换为中文
	//SlAiDataHandle::Get()->ChangeLocalizationCulture(ECultureTeam::ZH);
	ChangeCulture.ExecuteIfBound(ECultureTeam::ZH);
}

void SSlAiGameOptionWidget::EnCheckBoxStateChanged(ECheckBoxState NewState)
{
	//设置被选中的框
	EnCheckBox->SetIsChecked(ECheckBoxState::Checked);
	ZhCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
	//告诉数据控制类转换为中文
	//SlAiDataHandle::Get()->ChangeLocalizationCulture(ECultureTeam::EN);
	ChangeCulture.ExecuteIfBound(ECultureTeam::EN);
}

void SSlAiGameOptionWidget::MusicSliderChanged(float Value)
{
	//显示百分比
	MuTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(Value * 100)) + FString("%")));
	//修改音量
	//SlAiDataHandle::Get()->ResetMenuVolume(Value, -1.0f);
	ChangeVolume.ExecuteIfBound(Value, -1.0f);
}

void SSlAiGameOptionWidget::SoundSliderChanged(float Value)
{
	//显示百分比
	SoTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(Value * 100)) + FString("%")));
	//修改音量
	//SlAiDataHandle::Get()->ResetMenuVolume(-1.0f,Value);
	ChangeVolume.ExecuteIfBound(-1.0f, Value);
}
