// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SlAiTypes.h"
#include "SlAiPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SLAICOURSE_API ASlAiPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASlAiPlayerController();

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupInputComponent() override;

public:
	//获取玩家角色
	class ASlAiPlayerCharacter* SPCharacter;

protected:
	virtual void BeginPlay() override;
	
private:
	//切换视角
	void ChangeView();

	//鼠标按键事件
	void LeftEventStart();
	void LeftEventStop();
	void RightEventStart();
	void RightEventStop();

private:

	//左键预动作
	EUpperBody::Type LeftUpperType;

	//右键预动作
	EUpperBody::Type RightUpperType;
};
