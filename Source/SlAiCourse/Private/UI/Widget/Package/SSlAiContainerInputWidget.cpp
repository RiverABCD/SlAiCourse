// Fill out your copyright notice in the Description page of Project Settings.

#include "SSlAiContainerInputWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiContainerInputWidget::Construct(const FArguments& InArgs)
{
	SSlAiContainerBaseWidget::Construct(SSlAiContainerBaseWidget::FArguments().WorkIndex(InArgs._WorkIndex));
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
