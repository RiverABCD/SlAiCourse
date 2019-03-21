// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SLAICOURSE_API SlAiInternation
{
public:
	static void Register(FText Value) { return; }
};

#define LOCTEXT_NAMESPACE "SlAiMenu"

SlAiInternation::Register(LOCTEXT("Menu", "Menu"));//菜单
SlAiInternation::Register(LOCTEXT("StartGame", "StartGame"));//开始游戏
SlAiInternation::Register(LOCTEXT("GameOption", "GameOption"));//游戏设置
SlAiInternation::Register(LOCTEXT("QuitGame", "QuitGame"));//退出游戏

SlAiInternation::Register(LOCTEXT("NewGame", "NewGame"));//新游戏
SlAiInternation::Register(LOCTEXT("LoadRecord", "LoadRecord"));//加载存档

SlAiInternation::Register(LOCTEXT("ChooseRecord", "ChooseRecord"));//选择存档

//进入游戏界面
SlAiInternation::Register(LOCTEXT("RecordName", "RecordName"));//存档名
SlAiInternation::Register(LOCTEXT("EnterGame", "EnterGame"));//进入游戏
SlAiInternation::Register(LOCTEXT("EnterRecord", "EnterRecord"));//进入存档
SlAiInternation::Register(LOCTEXT("RecordNameHint", "Input Record Name!");//输入存档名
SlAiInternation::Register(LOCTEXT("NameRepeatedHint", "Record Name Repeated!");//输入存档名

//游戏设置界面
SlAiInternation::Register(LOCTEXT("Chinese", "Chinese"));//中文
SlAiInternation::Register(LOCTEXT("English", "English"));//英文
SlAiInternation::Register(LOCTEXT("Music", "Music"));//音乐
SlAiInternation::Register(LOCTEXT("Sound", "Sound"));//音效

//公用
SlAiInternation::Register(LOCTEXT("GoBack", "GoBack"));//返回

#undef LOCTEXT_NAMESPACE

//在一个域名空间内的本地化，同上define
//SlAiInternation::Register(NSLOCTEXT("SlAiMenu", "Menu", "Menu"));
