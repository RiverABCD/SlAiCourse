// Fill out your copyright notice in the Description page of Project Settings.

#include "SSlAiEnemyHPWidget.h"
#include "SlateOptMacros.h"
#include "SProgressBar.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiEnemyHPWidget::Construct(const FArguments& InArgs)
{

	
	ChildSlot
	[
		SAssignNew(HPBar,SProgressBar)
	];
	
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSlAiEnemyHPWidget::ChangeHP(float HP)
{
	HP = FMath::Clamp(HP, 0.f, 1.f);
	HPBar->SetPercent(HP);
	ResultColor = FLinearColor(1.f - HP, HP, 0.f, 1.f);
	HPBar->SetFillColorAndOpacity(FSlateColor(ResultColor));
}