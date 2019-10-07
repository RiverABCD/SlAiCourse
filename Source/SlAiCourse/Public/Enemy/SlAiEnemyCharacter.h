// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SlAiTypes.h"

#include "SlAiEnemyCharacter.generated.h"

UCLASS()
class SLAICOURSE_API ASlAiEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASlAiEnemyCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//实时更新血条的朝向,由Controller调用,传入玩家位置
	void UpdateHPBarRotation(FVector SPLoaction);

	//修改移动速度
	void SetMaxSpeed(float Speed);

	//获取Idle等待时长
	float GetIdleWaitTime();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	//武器插槽
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UChildActorComponent* WeaponSocket;
	//盾牌插槽
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UChildActorComponent* ShieldSocket;
	//血条(遗留问题)
	UPROPERTY(EditAnywhere, Category = Mesh)
		class UWidgetComponent* HPBar;
	
	//敌人感知
	UPROPERTY(EditAnywhere, Category = Mesh)
		class UPawnSensingComponent* EnemySense;

private:
	//绑定到敌人感知的方法
	UFUNCTION()
		void OnSeePlayer(APawn* PlayerChar);

private:
	//血条UI引用
	TSharedPtr<class SSlAiEnemyHPWidget> HPBarWidget;
	//控制器引用
	class ASlAiEnemyController* SEController;
	//血量
	float HP;
	//获取动作引用
	class USlAiEnemyAnim* SEAnim;
};
