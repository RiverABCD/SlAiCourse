// Fill out your copyright notice in the Description page of Project Settings.

#include "SSlAiPointerWidget.h"
#include "SlateOptMacros.h"
#include "SlAiStyle.h"
#include "SlAiGameWidgetStyle.h"
#include "SBox.h"
#include "SImage.h"
#include "Materials/MaterialInstanceDynamic.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiPointerWidget::Construct(const FArguments& InArgs)
{
	GameStyle = &SlAiStyle::Get().GetWidgetStyle<FSlAiGameStyle>("BPSlAiGameStyle");
	//初始化大小为20
	CurrentSize = 20.f;
	IsAimed = false;

	ChildSlot
	[
		SAssignNew(RootBox,SBox).WidthOverride(TAttribute<FOptionalSize>(this,&SSlAiPointerWidget::GetBoxWidth))
								.HeightOverride(TAttribute<FOptionalSize>(this,&SSlAiPointerWidget::GetBoxHeight))
		[
			SNew(SImage).Image(&GameStyle->PointerBrush)
		]
	];
	
	//加载材质实例
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> StaticPointerMaterialInstance(TEXT("MaterialInstanceConstant'/Game/Material/PointerMatInst.PointerMatInst'"));
	//转换为动态材质实例
	PointerMaterial = (UMaterialInstanceDynamic*)StaticPointerMaterialInstance.Object;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSlAiPointerWidget::Tick(const FGeometry & AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	//实时修改空间大小
	CurrentSize = IsAimed ? FMath::FInterpTo(CurrentSize, 130.f, InDeltaTime, 10.f) : FMath::FInterpTo(CurrentSize, 20.f, InDeltaTime, 10.f);
}

void SSlAiPointerWidget::UpdatePointer(bool IsAim, float Range)
{
	IsAimed = IsAim;
	PointerMaterial->SetScalarParameterValue(FName("Range"), Range);
}

FOptionalSize SSlAiPointerWidget::GetBoxWidth() const
{
	return FOptionalSize(CurrentSize);
}
FOptionalSize SSlAiPointerWidget::GetBoxHeight() const
{
	return FOptionalSize(CurrentSize);
}