// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SlAiGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SLAICOURSE_API ASlAiGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASlAiGameMode();
	//��д֡����
	virtual void Tick(float DeltaSeconds) override;

	//�����ֵ,��GameHUD����,����������������
	void InitGamePlayModule();
public:
	class ASlAiPlayerController* SPController;

	class ASlAiPlayerCharacter* SPCharacter;

	class ASlAiPlayerState* SPState;

protected:
	virtual void BeginPlay() override;
	
	
};
