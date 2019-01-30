// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SlAiMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class SLAICOURSE_API ASlAiMenuHUD : public AHUD
{
	GENERATED_BODY()
public:
	ASlAiMenuHUD();
	
	TSharedPtr<class SSlAiMenuHUDWidget> MenuHUDWidget;
};
