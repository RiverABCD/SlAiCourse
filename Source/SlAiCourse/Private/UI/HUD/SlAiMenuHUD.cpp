// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiMenuHUD.h"
#include "SSlAiMenuHUDWidget.h"
#include "SlateBasics.h"



ASlAiMenuHUD::ASlAiMenuHUD()
{
	if (GEngine&&GEngine->GameViewport)
	{
		SAssignNew(MenuHUDWidget, SSlAiMenuHUDWidget);
		GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(MenuHUDWidget.ToSharedRef()));

	}
}
