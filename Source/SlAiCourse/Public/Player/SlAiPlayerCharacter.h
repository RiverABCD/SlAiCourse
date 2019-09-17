// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SlAiTypes.h"
#include "SlAiPlayerCharacter.generated.h"

UCLASS()
class SLAICOURSE_API ASlAiPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASlAiPlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//修改视角
	void ChangeView(EGameViewMode::Type NewGameView);

	//修改当前的手持物品
	void ChangeHandObject(TSubclassOf<AActor> HandObjectClass);

	//修改手持物品的碰撞检测是否开启
	void ChangeHandObjectDetect(bool IsOpen);

	//是否渲染手上物品，由Anim进行调用
	void RenderHandObject(bool IsRender);

public:
	UPROPERTY(VisibleDefaultsOnly, Category = "SlAi")
		class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleDefaultsOnly, Category = "SlAi")
		class UCameraComponent* ThirdCamera;
	UPROPERTY(VisibleDefaultsOnly, Category = "SlAi")
		UCameraComponent* FirstCamera;

	//玩家控制器指针
	class ASlAiPlayerController* SPController;

	//当前的视角模型
	EGameViewMode::Type GameView;

	//上半身动画状态
	EUpperBody::Type UpperType;

	//是否允许切换视角
	bool IsAllowSwitch;

	//是否锁住输入
	bool IsInputLocked;

	//是否在攻击
	bool IsAttack;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUpAtRate(float Value);
	void Turn(float Value);
	void TurnAtRate(float Value);
	void OnStartJump();
	void OnStopJump();
	void OnStartRun();
	void OnStopRun();

private:
	//第一人称骨骼模型
	UPROPERTY(VisibleDefaultsOnly, Category = "SlAi")
		USkeletalMeshComponent* MeshFirst;

	//手上物品
	UPROPERTY(VisibleDefaultsOnly, Category = "SlAi")
		class UChildActorComponent* HandObject;

	//旋转比例
	float BaseLookUpRate;
	float BaseTurnRate;
	
	
};
