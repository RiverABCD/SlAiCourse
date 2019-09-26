// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "SlAiTypes.h"
#include "DeclarativeSyntaxSupport.h"
/**
 * 
 */
class SLAICOURSE_API SSlAiGameHUDWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiGameHUDWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	//绑定到UIScaler的方法
	float GetUIScaler() const;

	//显示游戏UI,被PlayerController的ShowGameUI委托绑定
	void ShowGameUI(EGameUIType::Type PreUI, EGameUIType::Type NextUI);
public:
	//快捷栏指针
	TSharedPtr<class SSlAiShortcutWidget> ShortcutWidget;
	//射线信息框
	TSharedPtr<class SSlAiRayInfoWidget> RayInfoWidget;
	//准星
	TSharedPtr<class SSlAiPointerWidget> PointerWidget;
	//玩家状态指针
	TSharedPtr<class SSlAiPlayerStateWidget> PlayerStateWidget;
	//游戏菜单
	TSharedPtr<class SSlAiGameMenuWidget> GameMenuWidget;
	//聊天室
	TSharedPtr<class SSlAiChatRoomWidget> ChatRoomWidget;
	//背包
	TSharedPtr<class SSlAiPackageWidget> PackageWidget;


private:
	//获取屏幕Size
	FVector2D GetViewportSize() const;

	//将UI绑定到UIMap
	void InitUIMap();

private:
	//DPI缩放
	TAttribute<float> UIScaler;

	//黑色遮罩
	TSharedPtr<class SBorder> BlackShade;

	//UIMap
	TMap<EGameUIType::Type, TSharedPtr<SCompoundWidget>> UIMap;
};
