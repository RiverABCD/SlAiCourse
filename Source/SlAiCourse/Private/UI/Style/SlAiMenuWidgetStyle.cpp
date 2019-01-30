// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiMenuWidgetStyle.h"


FSlAiMenuStyle::FSlAiMenuStyle()
{
}

FSlAiMenuStyle::~FSlAiMenuStyle()
{
}

const FName FSlAiMenuStyle::TypeName(TEXT("FSlAiMenuStyle"));

const FSlAiMenuStyle& FSlAiMenuStyle::GetDefault()
{
	static FSlAiMenuStyle Default;
	return Default;
}

void FSlAiMenuStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
}

