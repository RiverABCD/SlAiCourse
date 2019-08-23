// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiThirdPlayerAnim.h"
#include "SlAiPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SlAiHelper.h"
#include "Animation/AnimMontage.h"
#include "ConstructorHelpers.h"





USlAiThirdPlayerAnim::USlAiThirdPlayerAnim()
{
	//����Դ��Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerHitMon(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerHitMontage.PlayerHitMontage'"));
	PlayerHitMontage = PlayerHitMon.Object;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerEatMon(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerEatMontage.PlayerEatMontage'"));
	PlayerEatMontage = PlayerEatMon.Object;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerFightMon(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerFightMontage.PlayerFightMontage'"));
	PlayerFightMontage = PlayerFightMon.Object;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerPunchMon(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerPunchMontage.PlayerPunchMontage'"));
	PlayerPunchMontage = PlayerPunchMon.Object;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerPickUpMon(TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerPickUpMontage.PlayerPickUpMontage'"));
	PlayerPickUpMontage = PlayerPickUpMon.Object;

	//�����Լ��������˳��ǵ����˳�
	GameView = EGameViewMode::Third;

	//������ֵ
	Direction = 0.f;
	//���Ƿ��ڿ��и�ֵ
	IsInAir = false;
}

void USlAiThirdPlayerAnim::UpdateParameter()
{
	Super::UpdateParameter();
	//���������ֱ�ӷ��أ������ָ������ж�
	if (!SPCharacter) return;
	//����Ƿ�����Ծ
	IsInAir = SPCharacter->GetCharacterMovement()->IsFalling();
	//�ٶȳ����Yaw��ת��ȥActor������ʵ��������������Yaw��ת�õ���Եķ���
	float PreDir = SPCharacter->GetVelocity().ToOrientationRotator().Yaw - SPCharacter->GetActorRotation().Yaw;

#if 0
	//������ݰ������ŷ����
	//�ٶȳ���
	SlAiHelper::Debug(FString("SPCharacter->Velocity:") + FString::SanitizeFloat(SPCharacter->GetVelocity().ToOrientationRotator().Yaw),0.f);
	//���ﳯ��
	SlAiHelper::Debug(FString("SPCharacter:") + FString::SanitizeFloat(SPCharacter->GetActorRotation().Yaw),0.f);
	//����������ٶȸ����ﳯ��ļнǣ�
	SlAiHelper::Debug(FString("PreDir:") + FString::SanitizeFloat(PreDir), 0.f);
#endif

	//��������벻���׿���ȥ����˼·����һЩ
	if (PreDir > 180.f) PreDir -= 360.f;
	if (PreDir < -180.f) PreDir += 360.f;
	Direction = PreDir;
#if 0
	SlAiHelper::Debug(FString("Direction:") + FString::SanitizeFloat(Direction), 0.f);
#endif
}
