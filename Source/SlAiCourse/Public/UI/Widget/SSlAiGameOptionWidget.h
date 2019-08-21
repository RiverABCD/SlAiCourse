// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlAiTypes.h"
#include "Widgets/SCompoundWidget.h"

class SCheckBox;
class SSlider;
class STextBlock;

//�޸�����ί��
DECLARE_DELEGATE_OneParam(FChangeCulture, const ECultureTeam)
//�޸�����ί��
DECLARE_DELEGATE_TwoParams(FChangeVolume, const float, const float)

/**
 * 
 */
class SLAICOURSE_API SSlAiGameOptionWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiGameOptionWidget)
	{}
	SLATE_EVENT(FChangeCulture, ChangeCulture)
		SLATE_EVENT(FChangeVolume, ChangeVolume)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	//��ȡMenuStyle
	const struct FSlAiMenuStyle* MenuStyle;

	//��ȡcheckboxָ��
	TSharedPtr<SCheckBox> ZhCheckBox;
	TSharedPtr<SCheckBox> EnCheckBox;

	//����������
	TSharedPtr<SSlider> MuSlider;//��������
	TSharedPtr<SSlider> SoSlider;//��Ч
	//�������ٷֱ�
	TSharedPtr<STextBlock> MuTextBlock;
	TSharedPtr<STextBlock> SoTextBlock;

	//ί�б���
	FChangeCulture ChangeCulture;
	FChangeVolume ChangeVolume;


private:
	//ͳһ������ʽ
	void StyleInitialize();

	//����CheckBox�¼�
	void ZhCheckBoxStateChanged(ECheckBoxState NewState);
	//Ӣ��CheckBox�¼�
	void EnCheckBoxStateChanged(ECheckBoxState NewState);

	//�����仯�¼�
	void MusicSliderChanged(float Value);
	void SoundSliderChanged(float Value);
};
