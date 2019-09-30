// Fill out your copyright notice in the Description page of Project Settings.

#include "SSlAiContainerOutputWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiContainerOutputWidget::Construct(const FArguments& InArgs)
{
	SSlAiContainerBaseWidget::Construct(SSlAiContainerBaseWidget::FArguments().WorkIndex(InArgs._WorkIndex));
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSlAiContainerOutputWidget::LeftOperate(int InputID, int InputNum, int& OutputID, int& OutputNum)
{
	//如果本地物品为空,输入啥就返回啥,直接return
	if (ObjectIndex == 0) {
		OutputID = InputID;
		OutputNum = InputNum;
		return;
	}

	//以下都是输入物品不为空的状态

	//如果输入物品与本地物品相同并且可以叠加
	if (InputID == ObjectIndex && MultiplyAble(InputID))
	{
		OutputID = ObjectIndex;
		OutputNum = (InputNum + ObjectNum <= 64) ? (InputNum + ObjectNum) : 64;
		ObjectNum = (InputNum + ObjectNum <= 64) ? 0 : (InputNum + ObjectNum - 64);
		//执行合成输出委托
		CompoundOutput.ExecuteIfBound(ObjectIndex, OutputNum - InputNum);
		//直接return
		return;
	}

	//如果物品不相同或者物品相同但是不能叠加,输出物品,丢弃输入物品
	OutputID = ObjectIndex;
	OutputNum = ObjectNum;
	//执行合成输出委托
	CompoundOutput.ExecuteIfBound(ObjectIndex, ObjectNum);
	//执行丢弃物品委托
	ThrowObject.ExecuteIfBound(InputID, InputNum);
}

void SSlAiContainerOutputWidget::RightOperate(int InputID, int InputNum, int& OutputID, int& OutputNum)
{
	//如果本地物品为0
	if (ObjectIndex == 0) {
		OutputID = InputID;
		OutputNum = InputNum;
		return;
	}

	//以下都是本地物品不为0的情况

	//如果输入为空,直接给出本地的一半
	if (InputID == 0) {
		OutputID = ObjectIndex;
		//区别单数双数
		OutputNum = (ObjectNum % 2 == 1) ? (ObjectNum / 2 + 1) : (ObjectNum / 2);
		//执行合成输出委托
		CompoundOutput.ExecuteIfBound(ObjectIndex, OutputNum);
		//更新属性
		//ResetContainerPara(ObjectNum - OutputNum == 0 ? 0 : ObjectIndex, ObjectNum - OutputNum);
		//直接返回
		return;
	}

	//以下都是输入不为空的情况

	//如果物品相同并且可以合并,给出去一半
	if (InputID == ObjectIndex && MultiplyAble(InputID)) {
		OutputID = ObjectIndex;
		//预备输出的数量
		int PreOutputNum = (ObjectNum % 2 == 1) ? (ObjectNum / 2 + 1) : (ObjectNum / 2);
		//实际输出的数量
		OutputNum = (PreOutputNum + InputNum <= 64) ? (PreOutputNum + InputNum) : 64;
		//更新本地数量
		ObjectNum = ObjectNum - (OutputNum - InputNum);
		//执行合成输出委托
		CompoundOutput.ExecuteIfBound(ObjectIndex, OutputNum - InputNum);
		//更新属性
		//ResetContainerPara(ObjectNum == 0 ? 0 : ObjectIndex, ObjectNum);
		//直接返回
		return;
	}


	//如果物品不相同或者相同但是不能合并,把输入物品丢弃,输出本地物品的一半
	OutputID = ObjectIndex;
	//区别单数双数
	OutputNum = (ObjectNum % 2 == 1) ? (ObjectNum / 2 + 1) : (ObjectNum / 2);
	//执行合成输出委托
	CompoundOutput.ExecuteIfBound(ObjectIndex, OutputNum);
	//执行丢弃物品委托
	ThrowObject.ExecuteIfBound(InputID, InputNum);

}

