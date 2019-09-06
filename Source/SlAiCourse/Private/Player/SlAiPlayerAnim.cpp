// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiPlayerAnim.h"


USlAiPlayerAnim::USlAiPlayerAnim()
{
	Speed = 0.f;
	SpineRotator = FRotator(0.f, 0.f, 0.f);
}

void USlAiPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	//��ʼ����ɫָ��
	InitSPCharacter();
	//������ͼ����
	UpdateParameter();
	//���¶���
	UpdateMontage();
}

void USlAiPlayerAnim::ChangeDetection(bool IsOpen)
{
	if (!SPCharacter) return;
	SPCharacter->ChangeHandObjectDetect(IsOpen);
}

void USlAiPlayerAnim::InitSPCharacter()
{
	if (!SPCharacter) SPCharacter = Cast<ASlAiPlayerCharacter>(TryGetPawnOwner());
}

void USlAiPlayerAnim::UpdateParameter()
{
	if (!SPCharacter) return;
	//�����ٶ�
	Speed = SPCharacter->GetVelocity().Size();

	//�����ϰ������ת
	float SpineDir = SPCharacter->GetActorRotation().Yaw - 90.f;
	if (SpineDir > 180.f) SpineDir -= 360.f;
	if (SpineDir < -180.f) SpineDir += 360.f;
	SpineRotator = FRotator(0.f, SpineDir, 90.f);
}

void USlAiPlayerAnim::UpdateMontage()
{
	//���������ֱ�ӷ���,�����ָ������ж�
	if (!SPCharacter) return;

	//�����ǰ���˳�״̬����������Ĳ�һ��,ֱ�ӷ���
	if (SPCharacter->GameView != GameView) return;

	//�����ǰ�Ķ���û��ֹͣ,�����¶���
	if (!Montage_GetIsStopped(CurrentMontage)) return;

	switch (SPCharacter->UpperType)
	{
	case EUpperBody::None:
		//������ĸ������ڲ���
		if (CurrentMontage!=nullptr)
		{
			Montage_Stop(0);
			CurrentMontage = nullptr;
			//�����л��ӽ�
			AllowViewChange(true);
		}
		break;
	case EUpperBody::Punch:
		if (!Montage_IsPlaying(PlayerPunchMontage))
		{
			Montage_Play(PlayerPunchMontage);
			CurrentMontage = PlayerPunchMontage;
			//�������л��ӽ�
			AllowViewChange(false);
		}
		break;
	case EUpperBody::Hit:
		if (!Montage_IsPlaying(PlayerHitMontage))
		{
			Montage_Play(PlayerHitMontage);
			CurrentMontage = PlayerHitMontage;
			AllowViewChange(false);
		}
		break;
	case EUpperBody::Fight:
		if (!Montage_IsPlaying(PlayerFightMontage))
		{
			Montage_Play(PlayerFightMontage);
			CurrentMontage = PlayerFightMontage;
			AllowViewChange(false);
		}
		break;
	case EUpperBody::PickUp:
		if (!Montage_IsPlaying(PlayerPickUpMontage))
		{
			Montage_Play(PlayerPickUpMontage);
			CurrentMontage = PlayerPickUpMontage;
			AllowViewChange(false);
		}
		break;
	case EUpperBody::Eat:
		if (!Montage_IsPlaying(PlayerEatMontage))
		{
			Montage_Play(PlayerEatMontage);
			CurrentMontage = PlayerEatMontage;
			AllowViewChange(false);
		}
		break;
	}
}

void USlAiPlayerAnim::AllowViewChange(bool IsAllow)
{
	if (!SPCharacter) return;
	SPCharacter->IsAllowSwitch = IsAllow;
}
