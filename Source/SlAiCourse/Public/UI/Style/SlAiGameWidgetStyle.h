﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "SlateWidgetStyleContainerBase.h"
#include "SlateBrush.h"
#include "SlateFontInfo.h"

#include "SlAiGameWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct SLAICOURSE_API FSlAiGameStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FSlAiGameStyle();
	virtual ~FSlAiGameStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FSlAiGameStyle& GetDefault();

	//指定快捷栏的容器图标,把快捷栏的Style指定到Package
	UPROPERTY(EditAnywhere, Category = Package)
		FSlateBrush NormalContainerBrush;

	//指定被选择的容器的Brush
	UPROPERTY(EditAnywhere, Category = Package)
		FSlateBrush ChoosedContainerBrush;

	//指定没有颜色的Brush
	UPROPERTY(EditAnywhere, Category = Package)
		FSlateBrush EmptyBrush;

	//背包的背景框
	UPROPERTY(EditAnywhere, Category = Package)
		FSlateBrush PackageBGBrush;

	//合成表箭头
	UPROPERTY(EditAnywhere, Category = Package)
		FSlateBrush CompoundArrowBrush;

	//物品的Brush
	UPROPERTY(EditAnywhere, Category = Package)
		FSlateBrush ObjectBrush_1;
	UPROPERTY(EditAnywhere, Category = Package)
		FSlateBrush ObjectBrush_2;
	UPROPERTY(EditAnywhere, Category = Package)
		FSlateBrush ObjectBrush_3;
	UPROPERTY(EditAnywhere, Category = Package)
		FSlateBrush ObjectBrush_4;
	UPROPERTY(EditAnywhere, Category = Package)
		FSlateBrush ObjectBrush_5;
	UPROPERTY(EditAnywhere, Category = Package)
		FSlateBrush ObjectBrush_6;
	UPROPERTY(EditAnywhere, Category = Package)
		FSlateBrush ObjectBrush_7;

	//射线检测信息面板背景
	UPROPERTY(EditAnywhere, Category = Info)
		FSlateBrush RayInfoBrush;
	//准星Brush
	UPROPERTY(EditAnywhere, Category = Info)
		FSlateBrush PointerBrush;
	//主角图标
	UPROPERTY(EditAnywhere, Category = MiniMap)
		FSlateBrush PawnPointBrush;
	//小地图背景图片
	UPROPERTY(EditAnywhere, Category = MiniMap) 
		FSlateBrush MiniMapBGBrush;
	//玩家属性背景图
	UPROPERTY(EditAnywhere, Category = PlayerState)
		FSlateBrush PlayerStateBGBrush;

	//玩家头像背景图片
	UPROPERTY(EditAnywhere, Category = PlayerState)
		FSlateBrush PlayerHeadBGBrush;

	//血条Brush
	UPROPERTY(EditAnywhere, Category = PlayerState)
		FSlateBrush HPBrush;

	//饥饿Brush
	UPROPERTY(EditAnywhere, Category = PlayerState)
		FSlateBrush HungerBrush;

	//玩家头像
	UPROPERTY(EditAnywhere, Category = PlayerState)
		FSlateBrush PlayerHeadBrush;

	//聊天室背景图片
	UPROPERTY(EditAnywhere, Category = ChatRoom)
		FSlateBrush ChatRoomBGBrush;

	/*
	* 60号字体
	*/
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_60;

	/*
	* 50号字体有轮廓
	*/
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_Outline_50;

	/*
	* 40号字体
	*/
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_40;

	/*
	* 40号字体有轮廓
	*/
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_Outline_40;

	/*
	* 30号字体
	*/
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_30;

	/*
	* 20号字体
	*/
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_20;

	/*
	* 20号字体有轮廓
	*/
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_Outline_20;

	/*
	* 16号字体有轮廓
	*/
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_Outline_16;

	/*
	* 16号字体
	*/
	UPROPERTY(EditAnywhere, Category = Common)
		FSlateFontInfo Font_16;


	/*
	* 黑色颜色
	*/
	UPROPERTY(EditAnywhere, Category = Common)
		FLinearColor FontColor_White;

	/*
	* 白色颜色
	*/
	UPROPERTY(EditAnywhere, Category = Common)
		FLinearColor FontColor_Black;
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class USlAiGameWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FSlAiGameStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
