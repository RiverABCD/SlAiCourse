// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlAiTypes.h"
#include "Widgets/SCompoundWidget.h"

//注册快捷栏到PlayerState类的委托
DECLARE_DELEGATE_TwoParams(FRegisterShortcutContainer,TArray<TSharedPtr<ShortcutContainer>>*,TSharedPtr<STextBlock>)
/**
 * 
 */
class SLAICOURSE_API SSlAiShortcutWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiShortcutWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	
public:
	FRegisterShortcutContainer RegisterShortcutContainer;
private:

	//初始化所有容器
	void InitializeContainer();

private:
	//获取GameStyle
	const struct FSlAiGameStyle* GameStyle;
	//物品信息的指针
	TSharedPtr<class STextBlock> ShortcutInfoTextBlock;
	//网格指针
	TSharedPtr<class SUniformGridPanel> GridPanel;
	//是否初始化容器
	bool IsInitializeContainer;

};
