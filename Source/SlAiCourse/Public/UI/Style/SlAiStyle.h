// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"

/**
 * 
 */
class SLAICOURSE_API SlAiStyle
{
public:
	static void Initialize();
	//获取注册样式的名字
	static FName GetStyleSetName();
	//游戏关闭的时候取消注册
	static void ShutDown();
	//外部调用获取这个单例
	static const ISlateStyle& Get();

private:
	// FSlateStyleSet--注册样式
	static TSharedRef<class FSlateStyleSet> Create();

	static TSharedPtr<FSlateStyleSet> SlAiStyleInstance;
};
