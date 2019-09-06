// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hand/SlAiHandObject.h"
#include "SlAiHandStone.generated.h"

/**
 * 
 */
UCLASS()
class SLAICOURSE_API ASlAiHandStone : public ASlAiHandObject
{
	GENERATED_BODY()
	
public:
	ASlAiHandStone();
protected:
	virtual void BeginPlay() override;
	
	
};
