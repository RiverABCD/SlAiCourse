// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SlAiGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class SLAICOURSE_API ASlAiGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ASlAiGameHUD();
public:
	//保存GameMode指针
	class ASlAiGameMode* GM;
protected:
	virtual void BeginPlay() override;
private:
	TSharedPtr<class SSlAiGameHUDWidget> GameHUDWidget;
};
