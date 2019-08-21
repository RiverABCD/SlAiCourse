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
	//��ȡ�༭����MenuStyle
	MenuStyle = &SlAiStyle::Get().GetWidgetStyle < FSlAiMenuStyle >("BPSlAiMenuStyle");
	
	//��ȡί��
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
				//��һ��
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
				//�ڶ���
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

			//������
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
	////����ZhCheckBox��ʽ
	ZhCheckBox->SetUncheckedImage(&MenuStyle->UnCheckedBoxBrush);
	ZhCheckBox->SetUncheckedHoveredImage(&MenuStyle->UnCheckedBoxBrush);
	ZhCheckBox->SetUncheckedPressedImage(&MenuStyle->UnCheckedBoxBrush);
	ZhCheckBox->SetCheckedImage(&MenuStyle->CheckedBoxBrush);
	ZhCheckBox->SetCheckedHoveredImage(&MenuStyle->CheckedBoxBrush);
	ZhCheckBox->SetCheckedPressedImage(&MenuStyle->CheckedBoxBrush);

	//����EnCheckBox��ʽ
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
	//���ñ�ѡ�еĿ�
	EnCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
	ZhCheckBox->SetIsChecked(ECheckBoxState::Checked);
	//�������ݿ�����ת��Ϊ����
	//SlAiDataHandle::Get()->ChangeLocalizationCulture(ECultureTeam::ZH);
	ChangeCulture.ExecuteIfBound(ECultureTeam::ZH);
}

void SSlAiGameOptionWidget::EnCheckBoxStateChanged(ECheckBoxState NewState)
{
	//���ñ�ѡ�еĿ�
	EnCheckBox->SetIsChecked(ECheckBoxState::Checked);
	ZhCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
	//�������ݿ�����ת��Ϊ����
	//SlAiDataHandle::Get()->ChangeLocalizationCulture(ECultureTeam::EN);
	ChangeCulture.ExecuteIfBound(ECultureTeam::EN);
}

void SSlAiGameOptionWidget::MusicSliderChanged(float Value)
{
	//��ʾ�ٷֱ�
	MuTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(Value * 100)) + FString("%")));
	//�޸�����
	//SlAiDataHandle::Get()->ResetMenuVolume(Value, -1.0f);
	ChangeVolume.ExecuteIfBound(Value, -1.0f);
}

void SSlAiGameOptionWidget::SoundSliderChanged(float Value)
{
	//��ʾ�ٷֱ�
	SoTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(Value * 100)) + FString("%")));
	//�޸�����
	//SlAiDataHandle::Get()->ResetMenuVolume(-1.0f,Value);
	ChangeVolume.ExecuteIfBound(-1.0f, Value);
}
