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
	//重写帧函数
	virtual void Tick(float DeltaSeconds) override;

	//组件赋值,给GameHUD调用,避免空引用引起崩溃
	void InitGamePlayModule();
public:
	class ASlAiPlayerController* SPController;

	class ASlAiPlayerCharacter* SPCharacter;

	class ASlAiPlayerState* SPState;

protected:
	virtual void BeginPlay() override;
	
	
};
