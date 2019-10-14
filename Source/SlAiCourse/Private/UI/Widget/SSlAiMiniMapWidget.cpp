// Fill out your copyright notice in the Description page of Project Settings.

#include "SSlAiMiniMapWidget.h"
#include "SlateOptMacros.h"
#include "SlAiStyle.h"
#include "SlAiGameWidgetStyle.h"
#include "SBox.h"
#include "SImage.h"
#include "SOverlay.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/TextureRenderTarget2D.h"
#include "SlateBrush.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiMiniMapWidget::Construct(const FArguments& InArgs)
{
	//获取GameStyle
	GameStyle = &SlAiStyle::Get().GetWidgetStyle<FSlAiGameStyle>("BPSlAiGameStyle");
	
	ChildSlot
	[
		SNew(SBox).WidthOverride(320.f).HeightOverride(320.f)
		[
			SNew(SOverlay)
			//MiniMap背景图片
			+ SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill)
			[
				SNew(SImage).Image(&GameStyle->MiniMapBGBrush)
			]
			//渲染MiniMap的图片
			+ SOverlay::Slot().HAlign(HAlign_Center).VAlign(VAlign_Center)
			[
				SAssignNew(MiniMapImage, SImage)
			]
	
		]
	];
	
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSlAiMiniMapWidget::RegisterMiniMap(class UTextureRenderTarget2D* MiniMapRender)
{
	//获取材质,这个材质是遮罩
	UMaterialInterface* MiniMapMatInst = LoadObject<UMaterialInterface>(NULL, TEXT("MaterialInstanceConstant'/Game/Material/MiniMapMatInst.MiniMapMatInst'"));
	//创建动态材质
	UMaterialInstanceDynamic* MiniMapMatDynamic = UMaterialInstanceDynamic::Create(MiniMapMatInst, nullptr);
	//绑定材质属性
	MiniMapMatDynamic->SetTextureParameterValue(FName("MiniMapTex"), MiniMapRender);
	//实例化MiniMap笔刷
	MiniMapBrush = new FSlateBrush();
	//设置属性
	MiniMapBrush->ImageSize = FVector2D(280.f, 280.f);
	MiniMapBrush->DrawAs = ESlateBrushDrawType::Image;
	//绑定材质资源文件
	MiniMapBrush->SetResourceObject(MiniMapMatDynamic);
	//将笔刷作为MiniMapImage的笔刷
	MiniMapImage->SetImage(MiniMapBrush);
}
