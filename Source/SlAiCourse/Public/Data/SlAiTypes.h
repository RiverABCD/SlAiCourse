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