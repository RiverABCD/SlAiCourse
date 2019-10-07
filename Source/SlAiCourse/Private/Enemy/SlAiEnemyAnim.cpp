// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiEnemyAnim.h"
#include "SlAiEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimSequence.h"
#include "ConstructorHelpers.h"

USlAiEnemyAnim::USlAiEnemyAnim()
{
	static ConstructorHelpers::FObjectFinder<UAnimSequence> StaticAnimIdle_I(TEXT("AnimSequence'/Game/Res/PolygonAdventure/Mannequin/Enemy/Animation/MoveGroup/Enemy_Idle_I.Enemy_Idle_I'"));
	AnimIdle_I = StaticAnimIdle_I.Object;
	static ConstructorHelpers::FObjectFinder<UAnimSequence> StaticAnimIdle_II(TEXT("AnimSequence'/Game/Res/PolygonAdventure/Mannequin/Enemy/Animation/MoveGroup/Enemy_Idle_II.Enemy_Idle_II'"));
	AnimIdle_II = StaticAnimIdle_II.Object;
	static ConstructorHelpers::FObjectFinder<UAnimSequence> StaticAnimIdle_III(TEXT("AnimSequence'/Game/Res/PolygonAdventure/Mannequin/Enemy/Animation/MoveGroup/Enemy_Idle_III.Enemy_Idle_III'"));
	AnimIdle_III = StaticAnimIdle_III.Object;

	//初始化参数
	Speed = 0.f;
	IdleType = 0.f;
}

void USlAiEnemyAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	//初始化角色指针
	if (!SECharacter) SECharacter = Cast<ASlAiEnemyCharacter>(TryGetPawnOwner());
	if (!SECharacter) return;

	//设置速度
	Speed = SECharacter->GetVelocity().Size();
}

//设置Idle模式,返回动作时长
float USlAiEnemyAnim::SetIdelType(int NewType)
{
	IdleType = FMath::Clamp<float>((float)NewType, 0.f, 2.f);
	switch (NewType)
	{
	case 0:
		return AnimIdle_I->GetPlayLength();
	case 1:
		return AnimIdle_II->GetPlayLength();
	case 2:
		return AnimIdle_III->GetPlayLength();
	}
	return AnimIdle_I->GetPlayLength();
}