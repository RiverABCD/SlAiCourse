// Fill out your copyright notice in the Description page of Project Settings.

#include "SSlAiContainerShortcutWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiContainerShortcutWidget::Construct(const FArguments& InArgs)
{
	SSlAiContainerBaseWidget::Construct(SSlAiContainerBaseWidget::FArguments().WorkIndex(InArgs._WorkIndex));
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSlAiContainerShortcutWidget::ResetContainerPara(int ObjectID, int Num)
{
	//定义是否改变
	bool IsChanged = false;
	if (ObjectIndex != ObjectID || ObjectNum != Num) IsChanged = true;

	//调用父类事件
	SSlAiContainerBaseWidget::ResetContainerPara(ObjectID, Num);


	//如果有改变, 执行快捷栏修改更新委托,传出快捷栏序号以及新的物品ID
	if (IsChanged) PackShortChange.ExecuteIfBound(WorkIndex.Get(), ObjectID, Num);
}