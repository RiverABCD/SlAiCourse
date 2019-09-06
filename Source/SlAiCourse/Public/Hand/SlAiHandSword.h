// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hand/SlAiHandObject.h"
#include "SlAiHandSword.generated.h"

/**
 * 
 */
UCLASS()
class SLAICOURSE_API ASlAiHandSword : public ASlAiHandObject
{
	GENERATED_BODY()
	
public:
	ASlAiHandSword();
protected:
	virtual void BeginPlay() override;
	
	
};
