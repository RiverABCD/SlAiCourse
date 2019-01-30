// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"

/**
 * 
 */
class SLAICOURSE_API SlAiStyle
{
public:
	static void Initialize();

	static FName GetStyleSetName();

	static void ShutDown();

	static const ISlateStyle& Get();

private:
	// FSlateStyleSet--ע����ʽ
	static TSharedRef<class FSlateStyleSet> Create();

	static TSharedPtr<FSlateStyleSet> SlAiStyleInstance;
};
