// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SlAiTypes.h"
#include "SlAiPlayerCharacter.h"
#include "SlAiPlayerState.h"
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
	class ASlAiPlayerState* SPState;

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

	//鼠标滚轮上下滑动事件
	void ScrollUpEvent();
	void ScrollDownEvent();
private:

	//左键预动作
	EUpperBody::Type LeftUpperType;

	//右键预动作
	EUpperBody::Type RightUpperType;

	//是否按住左右鼠标键
	bool IsLeftButtonDown;
	bool IsRightButtonDown;
};
