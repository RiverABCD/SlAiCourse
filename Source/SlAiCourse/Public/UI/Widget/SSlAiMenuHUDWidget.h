// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SOverlay.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SLAICOURSE_API SSlAiMenuHUDWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiMenuHUDWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	//��UIScaler�ĺ���
	float GetUIScaler() const;
	//��ȡ��Ļ�ߴ�
	FVector2D GetViewportSize() const;


private:

	//��ȡMenu��ʽ
	const struct FSlAiMenuStyle *MenuStyle;
	//DPI����ϵ��
	TAttribute<float> UIScaler;
	//�˵�ָ��
	TSharedPtr<class SSlAiMenuWidget> MenuWidget;
};
