// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "DeclarativeSyntaxSupport.h"

class SImage;
/**
 * 
 */
class SLAICOURSE_API SSlAiMiniMapWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiMiniMapWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	//委托接受GameMode传过来的Texture资源
	void RegisterMiniMap(class UTextureRenderTarget2D* MiniMapRender);

private:
	//获取GameStyle
	const struct FSlAiGameStyle* GameStyle;
	//显示MiniMap的图片
	TSharedPtr<SImage> MiniMapImage;


	//敌人视野材质
	class UMaterialInstanceDynamic* EnemyViewMatDynamic;

	struct FSlateBrush* MiniMapBrush;
};
