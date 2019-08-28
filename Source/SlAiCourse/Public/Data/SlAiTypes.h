// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBorder.h"
#include "SImage.h"
#include "STextBlock.h"
#include "SlateBasics.h"

/**
 * 
 */

UENUM()
enum class ECultureTeam : uint8 {
	EN = 0,
	ZH
};

//Menu按钮的类型
namespace EMenuItem {
	enum Type {
		None,
		StartGame,
		GameOption,
		QuitGame,
		NewGame,
		LoadRecord,
		StartGameGoBack,
		GameOptionGoBack,
		NewGameGoBack,
		ChooseRecordGoBack,
		EnterGame,
		EnterRecord
	};
}

//Menu界面类型
namespace EMenuType
{
	enum Type	
	{
		None,
		MainMenu,
		StartGame,
		GameOption,
		NewGame,
		ChooseRecord
	};
}

//Menu动画状态枚举
namespace EMenuAnim
{
	enum Type
	{
		Stop, //停止动画
		Close, //关闭Menu
		Open  //打开Menu
	};
}

//视角模式
namespace EGameViewMode {
	enum Type
	{
		First,
		Third
	};
}

//上半身动画的状态
namespace EUpperBody
{
	enum Type
	{
		None,
		Punch,
		Hit,
		Fight,
		PickUp,
		Eat
	};
}

//物品类型
namespace EObjectType
{
	enum Type
	{
		Normal = 0,//普通物品,木头,石头
		Food,//食物,苹果,肉
		Tool,//工具,锤子,斧子
		Weapon//武器,剑
	};
}

//物品属性结构体
struct ObjectAttribute
{
	FText EN;//英文名
	FText ZH;//中文名
	EObjectType::Type ObjectType;//物品类型
	int PlantAttack;//对植物的攻击力
	int MetalAttcck;//对金属资源的攻击力
	int AnimalAttack;//对动物的攻击力
	int AffectRange;//攻击距离
	FString TexPath;//图片路径
	//构造函数
	ObjectAttribute(const FText ENName, const FText ZHName, const EObjectType::Type OT, const int PA, const int MA, const int AA, const int AR, const FString TP)
	{
		EN = ENName;
		ZH = ZHName;
		ObjectType = OT;
		PlantAttack = PA;
		MetalAttcck = MA;
		AnimalAttack = AA;
		AffectRange = AR;
		TexPath = TP;
	}
#if 0
	FString ToString() {
		return EN.ToString() + FString("--") + ZH.ToString() + FString("--") + FString::FromInt((int)ObjectType) + FString("--") \
			+ FString::FromInt(PlantAttack) + FString("--") + FString::FromInt(MetalAttcck) + FString("--")\
			+ FString::FromInt(AnimalAttack) + FString("--") + FString::FromInt(AffectRange) + FString("--") + TexPath;

	}
#endif
};

//快捷栏容器结构体
struct ShortcutContainer
{
	//物品ID
	int ObjectIndex;
	int ObjectNum;
	TSharedPtr<SBorder> ContainerBorder;
	TSharedPtr<SBorder> ObjectImage;
	TSharedPtr<STextBlock> ObjectNumText;
	const FSlateBrush* NormalContainerBrush;
	const FSlateBrush* ChoosedContainerBrush;
	TArray<const FSlateBrush*>* ObjectBrushList;

	ShortcutContainer(TSharedPtr<SBorder> CB, TSharedPtr<SBorder> OI, TSharedPtr<STextBlock> ONT, const FSlateBrush* NCB, const FSlateBrush* CCB, TArray<const FSlateBrush*>* OBL)
	{
		ContainerBorder = CB;
		ObjectImage = OI;
		ObjectNumText = ONT;
		NormalContainerBrush = NCB;
		ChoosedContainerBrush = CCB;
		ObjectBrushList = OBL;

		//初始化显示设置
		ObjectIndex = 0;
		ObjectNum = 0;
		ContainerBorder->SetBorderImage(NormalContainerBrush);
		ObjectImage->SetBorderImage((*ObjectBrushList)[0]);
	}

	//设置是否选中当前的物品，true就是要选中，返回物品类型
	int SetChoosed(bool Option)
	{
		if (Option)
		{
			ContainerBorder->SetBorderImage(ChoosedContainerBrush);
		} 
		else
		{
			ContainerBorder->SetBorderImage(NormalContainerBrush);
		}
		return ObjectIndex;
	}

	//设置Index
	ShortcutContainer* SetObject(int NewIndex)
	{
		ObjectIndex = NewIndex;
		ObjectImage->SetBorderImage((*ObjectBrushList)[ObjectIndex]);
		return this;
	}

	//设置数量
	ShortcutContainer* SetObjectNum(int Num = 0)
	{
		ObjectNum = Num;
		//如果数量为0或者1，不现实数字
		if (ObjectNum == 0 || ObjectNum == 1)
		{
			ObjectNumText->SetText(FString(""));
		} 
		else
		{
			ObjectNumText->SetText(FString::FromInt(ObjectNum));
		}
		return this;
	}
};