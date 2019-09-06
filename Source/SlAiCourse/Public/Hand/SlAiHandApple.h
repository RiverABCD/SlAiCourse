// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hand/SlAiHandObject.h"
#include "SlAiHandApple.generated.h"

/**
 * 
 */
UCLASS()
class SLAICOURSE_API ASlAiHandApple : public ASlAiHandObject
{
	GENERATED_BODY()
	
public:
	ASlAiHandApple();
protected:
	virtual void BeginPlay() override;
	
};
