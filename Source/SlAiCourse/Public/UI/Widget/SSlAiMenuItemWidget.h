// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlAiTypes.h"
#include "Widgets/SCompoundWidget.h"

//����ί��
DECLARE_DELEGATE_OneParam(FItemClicked, const EMenuItem::Type)
/**
 * 
 */
class SLAICOURSE_API SSlAiMenuItemWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiMenuItemWidget)
	{}

	SLATE_ATTRIBUTE(FText,ItemText)
	SLATE_EVENT(FItemClicked, OnClicked)
	SLATE_ATTRIBUTE(EMenuItem::Type, ItemType)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	//��д�����OnMouseButtonDown����
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	//��д��ť�����ķ���
	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	//����뿪
	virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;

private:

	//��ȡ��ɫ
	FSlateColor GetTintColor() const;

private:
	//��ȡMenuStyle
	const struct FSlAiMenuStyle* MenuStyle;
	//�����¼�ί��
	FItemClicked OnClicked;
	//���水ť���� 
	EMenuItem::Type ItemType;
	//��ť�Ƿ��Ѿ�����
	bool IsMouseButtonDown;
};
