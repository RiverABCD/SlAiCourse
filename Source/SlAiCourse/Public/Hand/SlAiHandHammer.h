// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hand/SlAiHandObject.h"
#include "SlAiHandHammer.generated.h"

/**
 * 
 */
UCLASS()
class SLAICOURSE_API ASlAiHandHammer : public ASlAiHandObject
{
	GENERATED_BODY()
	
public:
	ASlAiHandHammer();
protected:
	virtual void BeginPlay() override;
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		UStaticMeshComponent* ExtendMesh;
	
};
