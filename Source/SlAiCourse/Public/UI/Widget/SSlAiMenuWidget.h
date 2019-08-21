// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlAiTypes.h"
#include "Widgets/SCompoundWidget.h"
#include "SSlAiGameOptionWidget.h"
#include "SSlAiNewGameWidget.h"
#include "SSlAiChooseRecordWidget.h"

class SBox;
class STextBlock;
class SVerticalBox;
struct MenuGroup;
class SSlAiGameOptionWidget;
class SSlAiNewGameWidget;
class SSlAiChooseRecordWidget;
/**
 * 
 */
class SLAICOURSE_API SSlAiMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiMenuWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	//重写tick函数
	virtual void Tick(const FGeometry& AllottedGeometry,const double InCurrentTime,const float InDeltaTime) override;

private:
	//绑定到各个MenuItem的方法
	void MenuItemOnClicked(EMenuItem::Type ItemType);
	//修改语言
	void ChangeCulture(ECultureTeam Culture);
	//修改音量
	void ChangeVolume(const float MusicVolume, const float SoundVolume);
	//初始化所有控件
	void InitializedMenuList();
	//选择显示的界面
	void ChooseWidget(EMenuType::Type WidgetType);
	//修改菜单的大小
	void ResetWidgetSize(float NewWidget, float NewHeight);
	//初始化动画组件
	void InitializedAnimation();
	//播放关闭动画
	void PlayClose(EMenuType::Type NewMenu);
	//退出游戏
	void QuitGame();
	//进入游戏
	void EnterGame();

private:
	//保存根节点
	TSharedPtr<SBox> RootSizeBox;
	//获取MenuStyle
	const struct FSlAiMenuStyle* MenuStyle;
	//保存标题
	TSharedPtr<STextBlock> TitleText;
	//用来保存垂直列表
	TSharedPtr<SVerticalBox> ContentBox;
	//保存菜单组
	TMap<EMenuType::Type, TSharedPtr<MenuGroup>> MenuMap;
	//游戏设置Widget指引
	TSharedPtr<SSlAiGameOptionWidget> GameOptionWidget;
	//新游戏空间指针
	TSharedPtr<SSlAiNewGameWidget> NewGameWidget;
	//选择存档空间指针
	TSharedPtr<SSlAiChooseRecordWidget> ChooseRecordWidget;

	//动画播放器
	FCurveSequence MenuAnimation;
	//曲线控制器
	FCurveHandle MenuCurve;
	//用来保存新的高度
	float CurrentHeight;
	//是否已经显示Menu组件
	bool IsMenuShow;
	//是否锁住按钮
	bool ControlLocked;
	//保存当前的动画状态
	EMenuAnim::Type AnimState;
	//保存当前的菜单
	EMenuType::Type CurrentMenu;
};
