// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSlAiContainerBaseWidget.h"
#include "DeclarativeSyntaxSupport.h"
/**
 * 
 */
class SLAICOURSE_API SSlAiContainerNormalWidget : public SSlAiContainerBaseWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiContainerNormalWidget)
	{}

	SLATE_ATTRIBUTE(int, WorkIndex)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};
