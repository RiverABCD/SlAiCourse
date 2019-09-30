// Fill out your copyright notice in the Description page of Project Settings.
#include "SSlAiContainerBaseWidget.h"
#include "SlateOptMacros.h"
#include "SlAiStyle.h"
#include "SlAiGameWidgetStyle.h"

#include "SBorder.h"
#include "STextBlock.h"

#include "SSlAiContainerNormalWidget.h"
#include "SSlAiContainerShortcutWidget.h"
#include "SSlAiContainerInputWidget.h"
#include "SSlAiContainerOutputWidget.h"
#include "SlAiDataHandle.h"

#include "SlAiHelper.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiContainerBaseWidget::Construct(const FArguments& InArgs)
{
	//获取GameStyle
	GameStyle = &SlAiStyle::Get().GetWidgetStyle<FSlAiGameStyle>("BPSlAiGameStyle");
	WorkIndex = InArgs._WorkIndex;

	ChildSlot
	[
		SAssignNew(ContainerBorder,SBorder).BorderImage(&GameStyle->NormalContainerBrush).Padding(FMargin(8.f))
		[
			SAssignNew(ObjectImage,SBorder).BorderImage(&GameStyle->EmptyBrush).HAlign(HAlign_Right).VAlign(VAlign_Bottom)
			.Padding(FMargin(0.f,0.f,4.f,0.f))
			[
				SAssignNew(ObjectNumText,STextBlock).Font(GameStyle->Font_Outline_16).ColorAndOpacity(GameStyle->FontColor_Black)
			]
		]
	];
	
	IsHover = false;
	//初始化时物品数量和序号都为0
	ObjectIndex = ObjectNum = 0;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

TSharedPtr<SSlAiContainerBaseWidget> SSlAiContainerBaseWidget::CreateContainer(EContainerType::Type NeedType, int WorkID)
{
	TSharedPtr<SSlAiContainerBaseWidget> ResultContainer;
	switch (NeedType)
	{
	case EContainerType::Output:
		SAssignNew(ResultContainer, SSlAiContainerOutputWidget).WorkIndex(WorkID);
		break;
	case EContainerType::Input:
		SAssignNew(ResultContainer, SSlAiContainerInputWidget).WorkIndex(WorkID);
		break;
	case EContainerType::Normal:
		SAssignNew(ResultContainer, SSlAiContainerNormalWidget).WorkIndex(WorkID);
		break;
	case EContainerType::Shortcut:
		SAssignNew(ResultContainer, SSlAiContainerShortcutWidget).WorkIndex(WorkID);
		break;
	}

	return ResultContainer;
}

void SSlAiContainerBaseWidget::UpdateHovered(bool IsHovered)
{
	//如果鼠标移动到上面
	if (IsHovered){
		if(!IsHover) ContainerBorder->SetBorderImage(&GameStyle->ChoosedContainerBrush);
		SlAiHelper::Debug(FString("ChoosedContainerBrush") , 0.f);
	}
	else{
		if(IsHover) ContainerBorder->SetBorderImage(&GameStyle->NormalContainerBrush);
		SlAiHelper::Debug(FString("NormalContainerBrush"), 0.f);
	}
	//更新当前状态
	IsHover = IsHovered;
}

void SSlAiContainerBaseWidget::ResetContainerPara(int ObjectID, int Num)
{
	//如果输入ID不相同,更新贴图
	if (ObjectIndex != ObjectID) ObjectImage->SetBorderImage(SlAiDataHandle::Get()->ObjectBrushList[ObjectID]);
	ObjectIndex = ObjectID;
	ObjectNum = Num;
	//如果物品ID为0
	if (ObjectIndex == 0) {
		ObjectNumText->SetText(FString(""));
	}
	else {
		//判断物品是否可以叠加,是的话显示数量
		if (MultiplyAble(ObjectID)){
			//显示数量
			ObjectNumText->SetText(FText::FromString(FString::FromInt(ObjectNum)));
		}
		else {
			//不可叠加的话不显示数量
			ObjectNumText->SetText(FText::FromString(""));
		}
	}
}

int SSlAiContainerBaseWidget::GetIndex() const
{

	return ObjectIndex;
}

int SSlAiContainerBaseWidget::GetNum() const
{
	return ObjectNum;
}

void SSlAiContainerBaseWidget::LeftOperate(int InputID, int InputNum, int & OutputID, int & OutputNum)
{
	//如果输入物品与本地物品相同并且可以叠加(即鼠标上的物品跟背包格子容器上的物品相同叠加)
	if (InputID == ObjectIndex && MultiplyAble(ObjectIndex))
	{
		//根据数量判断返回的ID
		OutputID = (ObjectNum + InputNum <= 64) ? 0 : InputID;
		//如果小于64,返回0, 大于则返回差值
		OutputNum = (ObjectNum + InputNum <= 64) ? 0 : (ObjectNum + InputNum - 64);
		//设置本地数量,上限为64
		ObjectNum = (ObjectNum + InputNum <= 64) ? (ObjectNum + InputNum) : 64;
		//更新属性
		ResetContainerPara(ObjectIndex, ObjectNum);
		//直接返回
		return;
	}
	//即鼠标上的物品跟背包格子容器上的物品相互交换
	//直接更换数据
	OutputID = ObjectIndex;
	OutputNum = ObjectNum;
	//更新属性
	ResetContainerPara(InputID, InputNum);
}

void SSlAiContainerBaseWidget::RightOperate(int InputID, int InputNum, int & OutputID, int & OutputNum)
{
	//如果输入为空,直接把本地的一半给出去,使用进一法
	if (InputID == 0)
	{
		OutputID = ObjectIndex;
		//区分单数双数
		OutputNum = (ObjectNum % 2 == 1) ? (ObjectNum / 2 + 1) : (ObjectNum / 2);
		//更新属性
		ResetContainerPara(ObjectNum - OutputNum == 0 ? 0 : ObjectIndex, ObjectNum - OutputNum);
		//直接返回
		return;
	}

	//如果物品相同并且物品可以合并  或者本地物品为空,添加一个到本地
	if (ObjectIndex == 0 || (InputID == ObjectIndex && MultiplyAble(InputID)))
	{
		//根据本地数量是否超出范围绑定输出数量
		OutputNum = (ObjectNum + 1 <= 64) ? (InputNum - 1) : InputNum;
		//根据数量是否为0定义输出ID
		OutputID = (OutputNum == 0) ? 0 : InputID;
		//更新属性
		ResetContainerPara(InputID, (ObjectNum + 1 <= 64) ? (ObjectNum + 1) : ObjectNum);
		//直接返回
		return;
	}
	//即鼠标上的物品跟背包格子容器上的物品相互交换
	//如果物品不相同或者相同但是不能合并,直接交换
	OutputID = ObjectIndex;
	OutputNum = ObjectNum;
	//更新属性
	ResetContainerPara(InputID, InputNum);
}

bool SSlAiContainerBaseWidget::RemainSpace(int ObjectID)
{
	if (ObjectIndex == ObjectID &&ObjectNum<64&& MultiplyAble(ObjectIndex)) return true;
	return false;
}

void SSlAiContainerBaseWidget::AddObject(int ObjectID)
{
	if (ObjectIndex == 0)
	{
		ResetContainerPara(ObjectID, 1);
		return;
	}
	if (ObjectIndex == ObjectID && ObjectNum < 64 && MultiplyAble(ObjectIndex)) {
		ResetContainerPara(ObjectIndex, ObjectNum + 1);
	}
}

bool SSlAiContainerBaseWidget::IsEmpty()
{
	return ObjectIndex == 0;
}

bool SSlAiContainerBaseWidget::MultiplyAble(int ObjectID)
{
	//获取物品属性
	TSharedPtr<ObjectAttribute> ObjectAttr = *SlAiDataHandle::Get()->ObjectAttrMap.Find(ObjectID);
	//返回是否是武器或者工具
	return (ObjectAttr->ObjectType != EObjectType::Tool&&ObjectAttr->ObjectType != EObjectType::Weapon);
}
