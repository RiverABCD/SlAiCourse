// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SlAiMenuController.generated.h"

/**
 * 
 */
UCLASS()
class SLAICOURSE_API ASlAiMenuController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASlAiMenuController();
protected:
	virtual void BeginPlay() override;
	
};
