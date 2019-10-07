// Fill out your copyright notice in the Description page of Project Settings.

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

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyAnim)
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EnemyAnim)
		float IdleType;
	
protected:

	//保存角色
	class ASlAiEnemyCharacter* SECharacter;

	//等待动作指针
	UAnimSequence* AnimIdle_I;
	UAnimSequence* AnimIdle_II;
	UAnimSequence* AnimIdle_III;
};
