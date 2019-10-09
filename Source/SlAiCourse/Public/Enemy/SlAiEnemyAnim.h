﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SlAiTypes.h"

#include "SlAiEnemyAnim.generated.h"

class UAnimSequence;
class UAnimMontage;
/**
 * 
 */
UCLASS()
class SLAICOURSE_API USlAiEnemyAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	USlAiEnemyAnim();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	//设置Idle模式,返回动作时长
	float SetIdelType(int NewType);

	//播放攻击动画,返回动画时长
	float PlayAttackAction(EEnemyAttackType AttackType);

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyAnim)
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyAnim)
		float IdleType;
	//根骨骼的位置
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyAnim)
		FVector RootBonePos;
	//根骨骼权重
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyAnim)
		float RootBoneAlpha;
	
protected:

	//保存角色
	class ASlAiEnemyCharacter* SECharacter;

	//等待动作指针
	UAnimSequence* AnimIdle_I;
	UAnimSequence* AnimIdle_II;
	UAnimSequence* AnimIdle_III;

	//攻击动画指针
	UAnimMontage* AnimAttack_I;
	UAnimMontage* AnimAttack_II;
	UAnimMontage* AnimAttack_III;
	UAnimMontage* AnimAttack_IV;

	UAnimSequence* AnimAttackSeq_III;
	UAnimSequence* AnimAttackSeq_IV;

	//动作计时器
	float CurrentPlayTime;
	//动作第一帧Y轴位置
	float StartYPos;
};
