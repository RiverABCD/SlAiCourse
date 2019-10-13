// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyTool/SlAiEnemyTool.h"
#include "SlAiEnemyWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SLAICOURSE_API ASlAiEnemyWeapon : public ASlAiEnemyTool
{
	GENERATED_BODY()
	
public:

	ASlAiEnemyWeapon();
protected:

	UFUNCTION()
		virtual void OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;

	
};
