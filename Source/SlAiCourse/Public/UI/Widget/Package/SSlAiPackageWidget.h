// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlAiTypes.h"
#include "Widgets/SCompoundWidget.h"
#include "DeclarativeSyntaxSupport.h"
/**
 * 
 */
class SLAICOURSE_API SSlAiPackageWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiPackageWidget)
	{}

	SLATE_ATTRIBUTE(float,UIScaler)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	//注册背包管理器事件,由playercharacter的InitPackageManager委托进行调用
	void InitPackageManager();

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

private:
	//获取MenuStyle
	const struct FSlAiGameStyle *GameStyle;


	//快捷栏表格
	TSharedPtr<class SUniformGridPanel> ShortcutGrid;

	//背包表格
	TSharedPtr<SUniformGridPanel> PackageGrid;

	//合成表表格
	TSharedPtr<SUniformGridPanel> CompoundGrid;

	//输出容器
	TSharedPtr<class SBorder> OutputBorder;

	//鼠标位置标定
	FVector2D MousePosition;

	//DPI的缩放
	TAttribute<float> UIScaler;

	//是否已经初始化背包管理器
	bool IsInitPackageMana;
};
