// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SlAiTypes.h"
#include "SlAiPlayerCharacter.h"
#include "SlAiPlayerState.h"
#include "SlAiPlayerController.generated.h"

//修改准星委托
DECLARE_DELEGATE_TwoParams(FUpdatePointer, bool, float)

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

	//对Character的手持物品进行更改,这个函数在playerstate内会调用
	void ChangeHandObject();

public:
	//获取玩家角色
	class ASlAiPlayerCharacter* SPCharacter;
	class ASlAiPlayerState* SPState;

	//实时修改准星的委托,注册的函数是PointerWidget的UpdatePointer
	FUpdatePointer UpdatePointer;

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

	//修改预动作
	void ChangePreUpperType(EUpperBody::Type RightType);
private:

	//左键预动作
	EUpperBody::Type LeftUpperType;

	//右键预动作
	EUpperBody::Type RightUpperType;

	//是否按住左右鼠标键
	bool IsLeftButtonDown;
	bool IsRightButtonDown;
};
