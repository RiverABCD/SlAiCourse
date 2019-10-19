// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "DeclarativeSyntaxSupport.h"
#include "SlAiTypes.h"

//存档委托
DECLARE_DELEGATE(FSaveGameDelegate)
/**
 * 
 */
class SLAICOURSE_API SSlAiGameMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiGameMenuWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	//失败方法
	void GameLose();

	//重置菜单
	void ResetMenu();

public:

	//存档委托,绑定GameMode的SaveGame函数
	FSaveGameDelegate SaveGameDele;

private:

	void InitializeWidget();

	FReply OptionEvent();
	FReply SaveGameEvent();
	FReply QuitGameEvent();
	FReply GoBackEvent();

	//改变语言
	void ChangeCulture(ECultureTeam Cultrue);
	//改变音量
	void ChangeVolume(const float MusicVolume, const float SoundVolume);

private:

	TSharedPtr<class SBox> RootBox;

	TSharedPtr<class SVerticalBox> VertBox;

	TSharedPtr<class SButton> SaveGameButton;

	TSharedPtr<class STextBlock> SaveGameText;

	TSharedPtr<SButton> QuitGameButton;

	TArray<TSharedPtr<SCompoundWidget>> MenuItemList;

	TArray<TSharedPtr<SCompoundWidget>> OptionItemList;

	//获取GameStyle
	const struct FSlAiGameStyle *GameStyle;
};
