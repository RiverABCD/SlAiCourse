// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "SlateWidgetStyleContainerBase.h"
#include "SlateBrush.h"
#include "SlateFontInfo.h"

#include "SlAiMenuWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct SLAICOURSE_API FSlAiMenuStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FSlAiMenuStyle();
	virtual ~FSlAiMenuStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FSlAiMenuStyle& GetDefault();

	UPROPERTY(EditAnywhere, Category = MenuHUD)
		FSlateBrush MenuHUDBackgroundBrush;
	/*
	* 指定Menu的背景图片
	*/
	UPROPERTY(EditAnywhere, Category = Menu)
		FSlateBrush MenuBackgroundBrush;
	/*
	* Menu左图标的Brush
	*/
	UPROPERTY(EditAnywhere, Category = Menu)
		FSlateBrush LeftIconBrush;
	/*
	* Menu右图标的Brush
	*/
	UPROPERTY(EditAnywhere, Category = Menu)
		FSlateBrush RightIconBrush;
	/*
	* Menu标题Border的Brush
	*/
	UPROPERTY(EditAnywhere, Category = Menu)
		FSlateBrush TitleBorderBrush;
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class USlAiMenuWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FSlAiMenuStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
