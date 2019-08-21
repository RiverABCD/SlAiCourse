// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class SEditableTextBox;
/**
 * 
 */
class SLAICOURSE_API SSlAiNewGameWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiNewGameWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	//�Ƿ���Խ�����Ϸ
	bool AllowEnterGame();

private:
	//��ȡMenuStyle
	const struct FSlAiMenuStyle* MenuStyle;

	//�����ָ��
	TSharedPtr<SEditableTextBox> EditTextBox;

};
