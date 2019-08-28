// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiGameWidgetStyle.h"


FSlAiGameStyle::FSlAiGameStyle()
{
}

FSlAiGameStyle::~FSlAiGameStyle()
{
}

const FName FSlAiGameStyle::TypeName(TEXT("FSlAiGameStyle"));

const FSlAiGameStyle& FSlAiGameStyle::GetDefault()
{
	static FSlAiGameStyle Default;
	return Default;
}

void FSlAiGameStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
}

