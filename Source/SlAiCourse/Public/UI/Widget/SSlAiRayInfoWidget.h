// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "DeclarativeSyntaxSupport.h"


class STextBlock;

DECLARE_DELEGATE_OneParam(FRegisterRayInfoEvent, TSharedPtr<STextBlock>)
/**
 *
 */
class SLAICOURSE_API SSlAiRayInfoWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiRayInfoWidget)
	{}
	SLATE_END_ARGS()

		/** Constructs this widget with InArgs */
		void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
public:
	FRegisterRayInfoEvent RegisterRayInfoEvent;

private:
	//������ʾ������Ϣ���ı�
	TSharedPtr<STextBlock> RayInfoTextBlock;
	//��ȡGameStyle
	const struct FSlAiGameStyle* GameStyle;
	//�Ƿ��Ѿ���ʼ���¼�
	bool IsInitRayInfoEvent;
};
