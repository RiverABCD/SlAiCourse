// Fill out your copyright notice in the Description page of Project Settings.
#include "SSlAiContainerBaseWidget.h"
#include "SlateOptMacros.h"
#include "SlAiStyle.h"
#include "SlAiGameWidgetStyle.h"

#include "SBorder.h"
#include "STextBlock.h"

#include "SSlAiContainerNormalWidget.h"
#include "SSlAiContainerShortcutWidget.h"
#include "SSlAiContainerInputWidget.h"
#include "SSlAiContainerOutputWidget.h"
#include "SlAiDataHandle.h"

#include "SlAiHelper.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiContainerBaseWidget::Construct(const FArguments& InArgs)
{
	//获取GameStyle
	GameStyle = &SlAiStyle::Get().GetWidgetStyle<FSlAiGameStyle>("BPSlAiGameStyle");
	WorkIndex = InArgs._WorkIndex;

	ChildSlot
	[
		SAssignNew(ContainerBorder,SBorder).BorderImage(&GameStyle->NormalContainerBrush).Padding(FMargin(8.f))
		[
			SAssignNew(ObjectImage,SBorder).BorderImage(&GameStyle->EmptyBrush).HAlign(HAlign_Right).VAlign(VAlign_Bottom)
			.Padding(FMargin(0.f,0.f,4.f,0.f))
			[
				SAssignNew(ObjectNumText,STextBlock).Font(GameStyle->Font_Outline_16).ColorAndOpacity(GameStyle->FontColor_Black)
			]
		]
	];
	
	IsHover = false;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

TSharedPtr<SSlAiContainerBaseWidget> SSlAiContainerBaseWidget::CreateContainer(EContainerType::Type NeedType, int WorkID)
{
	TSharedPtr<SSlAiContainerBaseWidget> ResultContainer;
	switch (NeedType)
	{
	case EContainerType::Output:
		SAssignNew(ResultContainer, SSlAiContainerOutputWidget).WorkIndex(WorkID);
		break;
	case EContainerType::Input:
		SAssignNew(ResultContainer, SSlAiContainerInputWidget).WorkIndex(WorkID);
		break;
	case EContainerType::Normal:
		SAssignNew(ResultContainer, SSlAiContainerNormalWidget).WorkIndex(WorkID);
		break;
	case EContainerType::Shortcut:
		SAssignNew(ResultContainer, SSlAiContainerShortcutWidget).WorkIndex(WorkID);
		break;
	}

	return ResultContainer;
}

void SSlAiContainerBaseWidget::UpdateHovered(bool IsHovered)
{
	//如果鼠标移动到上面
	if (IsHovered){
		if(!IsHover) ContainerBorder->SetBorderImage(&GameStyle->ChoosedContainerBrush);
		SlAiHelper::Debug(FString("ChoosedContainerBrush") , 0.f);
	}
	else{
		if(IsHover) ContainerBorder->SetBorderImage(&GameStyle->NormalContainerBrush);
		SlAiHelper::Debug(FString("NormalContainerBrush"), 0.f);
	}
	//更新当前状态
	IsHover = IsHovered;
}
