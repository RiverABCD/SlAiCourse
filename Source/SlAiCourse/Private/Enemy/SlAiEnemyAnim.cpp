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

	static ConstructorHelpers::FObjectFinder<UAnimMontage> StaticAnimAttack_I(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Enemy/Animation/FightGroup/MonEnemy_Attack_I.MonEnemy_Attack_I'"));
	AnimAttack_I = StaticAnimAttack_I.Object;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> StaticAnimAttack_II(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Enemy/Animation/FightGroup/MonEnemy_Attack_II.MonEnemy_Attack_II'"));
	AnimAttack_II = StaticAnimAttack_II.Object;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> StaticAnimAttack_III(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Enemy/Animation/FightGroup/MonEnemy_Attack_III.MonEnemy_Attack_III'"));
	AnimAttack_III = StaticAnimAttack_III.Object;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> StaticAnimAttack_IV(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Enemy/Animation/FightGroup/MonEnemy_Attack_IV.MonEnemy_Attack_IV'"));
	AnimAttack_IV = StaticAnimAttack_IV.Object;


	static ConstructorHelpers::FObjectFinder<UAnimSequence> StaticAnimAttackSeq_III(TEXT("AnimSequence'/Game/Res/PolygonAdventure/Mannequin/Enemy/Animation/FightGroup/Enemy_Attack_III.Enemy_Attack_III'"));
	AnimAttackSeq_III = StaticAnimAttackSeq_III.Object;
	static ConstructorHelpers::FObjectFinder<UAnimSequence> StaticAnimAttackSeq_IV(TEXT("AnimSequence'/Game/Res/PolygonAdventure/Mannequin/Enemy/Animation/FightGroup/Enemy_Attack_IV.Enemy_Attack_IV'"));
	AnimAttackSeq_IV = StaticAnimAttackSeq_IV.Object;


	//初始化参数
	Speed = 0.f;
	IdleType = 0.f;
	RootBonePos = FVector::ZeroVector;
	RootBoneAlpha = 0.f;
	CurrentPlayTime = 0.f;
	StartYPos = 0.f;
}

void USlAiEnemyAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	//初始化角色指针
	if (!SECharacter) SECharacter = Cast<ASlAiEnemyCharacter>(TryGetPawnOwner());
	if (!SECharacter) return;

	//设置速度
	Speed = SECharacter->GetVelocity().Size();

	//如果正在播放攻击三动画,实时修改根骨骼位置
	if (Montage_IsPlaying(AnimAttack_III))
	{
		CurrentPlayTime += DeltaSeconds;
		CurrentPlayTime = FMath::Clamp<float>(CurrentPlayTime, 0.f, AnimAttackSeq_III->GetPlayLength());
		FTransform OutputTrans;
		AnimAttackSeq_III->GetBoneTransform(OutputTrans, 0.f, CurrentPlayTime, true);
		RootBonePos = FVector(OutputTrans.GetLocation().X, StartYPos, OutputTrans.GetLocation().Z);
	}
	//else {
	//	Montage_Play(AnimAttack_III);
	//	CurrentPlayTime = 0.f;
	//	RootBonePos = FVector::ZeroVector;
	//	RootBoneAlpha = 1.f;
	//	//获取攻击三动画的第一帧的Y值
	//	AnimAttackSeq_III->GetBoneTransform(OutputTrans, 0, 0.f, true);
	//	StartYPos = OutputTrans.GetLocation().Y;
	//}
	//如果正在播放攻击四动画,实时修改根骨骼位置
	if (Montage_IsPlaying(AnimAttack_IV))
	{
		CurrentPlayTime += DeltaSeconds;
		CurrentPlayTime = FMath::Clamp<float>(CurrentPlayTime, 0.f, AnimAttackSeq_IV->GetPlayLength());
		FTransform OutputTrans;
		AnimAttackSeq_IV->GetBoneTransform(OutputTrans, 0.f, CurrentPlayTime, true);
		RootBonePos = FVector(OutputTrans.GetLocation().X, StartYPos, OutputTrans.GetLocation().Z);
	}

	//如果已经不再播放移动攻击动画,但是权重还大于0,在0.3秒秒内重置权重
	if (!Montage_IsPlaying(AnimAttack_III) && !Montage_IsPlaying(AnimAttack_IV) && RootBoneAlpha > 0.f)
	{
		RootBoneAlpha -= DeltaSeconds * 3;
		if (RootBoneAlpha < 0.f) RootBoneAlpha = 0.f;
	}

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

float USlAiEnemyAnim::PlayAttackAction(EEnemyAttackType AttackType)
{
	FRandomStream Stream;
	Stream.GenerateNewSeed();
	int SelectIndex = Stream.RandRange(0, 1);
	FTransform OutputTrans;
	switch (AttackType)
	{
	case EEnemyAttackType::EA_Normal:
		//选择随机播放普通攻击动作
		if (SelectIndex == 0)
		{
			Montage_Play(AnimAttack_I);
			return AnimAttack_I->GetPlayLength();
		}
		else
		{
			Montage_Play(AnimAttack_II);
			return AnimAttack_II->GetPlayLength();
		}
		break;
	case EEnemyAttackType::EA_Dash:
		//播放攻击三
		Montage_Play(AnimAttack_III);
		CurrentPlayTime = 0.f;
		RootBonePos = FVector::ZeroVector;
		RootBoneAlpha = 1.f;
		//获取攻击三动画的第一帧的Y值
		AnimAttackSeq_III->GetBoneTransform(OutputTrans, 0, 0.f, true);
		StartYPos = OutputTrans.GetLocation().Y;
		//返回时长
		return AnimAttack_III->GetPlayLength();
		break;
	case EEnemyAttackType::EA_Pursuit:
		//开始播放动画
		Montage_Play(AnimAttack_IV);
		CurrentPlayTime = 0;
		RootBonePos = FVector::ZeroVector;
		RootBoneAlpha = 1.f;
		//获取攻击四动画的第一帧的Y值
		AnimAttackSeq_IV->GetBoneTransform(OutputTrans, 0, 0.f, true);
		StartYPos = OutputTrans.GetLocation().Y;
		return AnimAttack_IV->GetPlayLength();
		break;
	}
	return 0.f;
}
