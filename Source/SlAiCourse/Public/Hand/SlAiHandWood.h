// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hand/SlAiHandObject.h"
#include "SlAiHandWood.generated.h"

/**
 * 
 */
UCLASS()
class SLAICOURSE_API ASlAiHandWood : public ASlAiHandObject
{
	GENERATED_BODY()
	
public:
	ASlAiHandWood();
protected:
	virtual void BeginPlay() override;
	
	
};
