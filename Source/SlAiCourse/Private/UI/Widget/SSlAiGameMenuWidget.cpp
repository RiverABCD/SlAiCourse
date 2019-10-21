// Fill out your copyright notice in the Description page of Project Settings.

#include "SSlAiGameMenuWidget.h"
#include "SlateOptMacros.h"
#include "SBox.h"
#include "SSlAiGameOptionWidget.h"
#include "SBoxPanel.h"
#include "SlAiStyle.h"
#include "SlAiGameWidgetStyle.h"
#include "STextBlock.h"
#include "SButton.h"

#include "SlAiDataHandle.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "SlAiPlayerController.h"
//#include "SlAiTypes.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiGameMenuWidget::Construct(const FArguments& InArgs)
{
	//获取GameStyle
	GameStyle = &SlAiStyle::Get().GetWidgetStyle<FSlAiGameStyle>("BPSlAiGameStyle");

	ChildSlot
	[
		SAssignNew(RootBox, SBox)
		.WidthOverride(600.f)
		.HeightOverride(400.f)
		.Padding(FMargin(50.f))
		[
			SAssignNew(VertBox, SVerticalBox)
		]
	];

	InitializeWidget();
}



END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSlAiGameMenuWidget::InitializeWidget()
{
	//初始化正常界面
	MenuItemList.Add(
		SNew(SButton).OnClicked(this, &SSlAiGameMenuWidget::OptionEvent).HAlign(HAlign_Center).VAlign(VAlign_Center)
		[
			SNew(STextBlock).Text(NSLOCTEXT("SlAiGame","GameOption","GameOption")).Font(GameStyle->Font_30)
		]
	);

	MenuItemList.Add(
		SAssignNew(SaveGameButton, SButton).OnClicked(this, &SSlAiGameMenuWidget::SaveGameEvent).HAlign(HAlign_Center).VAlign(VAlign_Center)
		[
			//这里做一个引用
			SAssignNew(SaveGameText, STextBlock).Text(NSLOCTEXT("SlAiGame", "SaveGame", "SaveGame")).Font(GameStyle->Font_30)
		]
	);

	MenuItemList.Add(
		SNew(SButton).OnClicked(this, &SSlAiGameMenuWidget::QuitGameEvent).HAlign(HAlign_Center).VAlign(VAlign_Center)
		[
			SNew(STextBlock).Text(NSLOCTEXT("SlAiGame", "QuitGame", "QuitGame")).Font(GameStyle->Font_30)
		]
	);

	//初始化游戏设置数组
	OptionItemList.Add(
		SNew(SSlAiGameOptionWidget).ChangeCulture(this, &SSlAiGameMenuWidget::ChangeCulture).ChangeVolume(this, &SSlAiGameMenuWidget::ChangeVolume)
	);
	OptionItemList.Add(
		SNew(SButton).OnClicked(this, &SSlAiGameMenuWidget::GoBackEvent).HAlign(HAlign_Center).VAlign(VAlign_Center)
		[
			SNew(STextBlock).Text(NSLOCTEXT("SlAiGame", "GoBack", "GoBack")).Font(GameStyle->Font_30)
		]
	);

	//初始化一个退出游戏按钮
	SAssignNew(QuitGameButton, SButton).OnClicked(this, &SSlAiGameMenuWidget::QuitGameEvent).HAlign(HAlign_Center).VAlign(VAlign_Center)
		[
			SNew(STextBlock).Text(NSLOCTEXT("SlAiGame", "QuitGame", "QuitGame")).Font(GameStyle->Font_30)
		];

	//将菜单按钮填充
	for (TArray<TSharedPtr<SCompoundWidget>>::TIterator It(MenuItemList); It; ++It)
	{
		VertBox->AddSlot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).Padding(10.f).FillHeight(1.f)
		[
			(*It)->AsShared()
		];
	}
}

FReply SSlAiGameMenuWidget::OptionEvent()
{
	//清空
	VertBox->ClearChildren();
	//将设置控件填充
	VertBox->AddSlot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).Padding(10.f).FillHeight(3.2f)
	[
		OptionItemList[0]->AsShared()
	];
	VertBox->AddSlot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).Padding(10.f).FillHeight(1.f)
	[
		OptionItemList[1]->AsShared()
	];
	//设置高度
	RootBox->SetHeightOverride(520.f);
	return FReply::Handled();
}

FReply SSlAiGameMenuWidget::SaveGameEvent()
{
	//保存存档
	SaveGameDele.ExecuteIfBound();
	//设置SaveGame按钮不可用
	SaveGameButton->SetVisibility(EVisibility::HitTestInvisible);
	//修改存档文字
	SaveGameText->SetText(NSLOCTEXT("SlAiGame", "SaveCompleted", "SaveCompleted"));
	//返回
	return FReply::Handled();
}

FReply SSlAiGameMenuWidget::QuitGameEvent()
{
	Cast<ASlAiPlayerController>(UGameplayStatics::GetPlayerController(GWorld, 0))->ConsoleCommand("quit");
	return FReply::Handled();
}

FReply SSlAiGameMenuWidget::GoBackEvent()
{
	//清空
	VertBox->ClearChildren();
	//将菜单按钮填充
	for (TArray<TSharedPtr<SCompoundWidget>>::TIterator It(MenuItemList); It; ++It)
	{
		VertBox->AddSlot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).Padding(10.f).FillHeight(1.f)
		[
			(*It)->AsShared()
		];
	}
	//设置高度
	RootBox->SetHeightOverride(400.f);
	return FReply::Handled();
}

void SSlAiGameMenuWidget::ChangeCulture(ECultureTeam Cultrue)
{
	SlAiDataHandle::Get()->ChangeLocalizationCulture(Cultrue);
}

void SSlAiGameMenuWidget::ChangeVolume(const float MusicVolume, const float SoundVolume)
{
	SlAiDataHandle::Get()->ResetGameVolume(MusicVolume, SoundVolume);
}

void SSlAiGameMenuWidget::GameLose()
{
	//清空
	VertBox->ClearChildren();

	VertBox->AddSlot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).Padding(10.f).FillHeight(1.f)
	[
		QuitGameButton->AsShared()
	];

	//设置高度
	RootBox->SetHeightOverride(200.f);
}

void SSlAiGameMenuWidget::ResetMenu()
{
	//清空
	VertBox->ClearChildren();
	//将菜单按钮填充
	for (TArray<TSharedPtr<SCompoundWidget>>::TIterator It(MenuItemList); It; ++It)
	{
		VertBox->AddSlot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).Padding(10.f).FillHeight(1.f)
		[
			(*It)->AsShared()
		];
	}
	//设置高度
	RootBox->SetHeightOverride(400.f);
	//重置存档按钮
	SaveGameButton->SetVisibility(EVisibility::Visible);
	//修改存档文字
	SaveGameText->SetText(NSLOCTEXT("SlAiGame", "SaveGame", "SaveGame"));
}