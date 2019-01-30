// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class SBox;
class STextBlock;
/**
 * 
 */
class SLAICOURSE_API SSlAiMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiMenuWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	//保存根节点
	TSharedPtr<SBox> RootSizeBox;
	//获取MenuStyle
	const struct FSlAiMenuStyle* MenuStyle;
	//保存标题
	TSharedPtr<STextBlock> TitleText;
};
