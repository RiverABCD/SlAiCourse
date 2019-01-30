// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiStyle.h"
#include "SlateGameResources.h"


//类似单例模式：给静态私有成员变量分配空间
TSharedPtr<FSlateStyleSet> SlAiStyle::SlAiStyleInstance = nullptr;

void SlAiStyle::Initialize()
{
	if (!SlAiStyleInstance.IsValid()) 
	{
		SlAiStyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*SlAiStyleInstance);
	}
}

FName SlAiStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("SlAiStyle"));
	return StyleSetName;
}

void SlAiStyle::ShutDown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*SlAiStyleInstance);
	ensure(SlAiStyleInstance.IsUnique());
	SlAiStyleInstance.Reset();
}

const ISlateStyle& SlAiStyle::Get()
{
	return *SlAiStyleInstance;
}

TSharedRef<class FSlateStyleSet> SlAiStyle::Create()
{
	TSharedRef<FSlateStyleSet> StyleRef = FSlateGameResources::New(SlAiStyle::GetStyleSetName(), "/Game/UI/Style", "/Game/UI/Style");
	StyleRef->Set("MenuItemFont", FSlateFontInfo("Roboto-Regular.ttf", 50));
	return StyleRef;
}
