// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiThirdPlayerAnim.h"
#include "SlAiPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SlAiHelper.h"
#include "Animation/AnimMontage.h"
#include "ConstructorHelpers.h"





USlAiThirdPlayerAnim::USlAiThirdPlayerAnim()
{
	//绑定资源到Montage
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

	//设置自己的运行人称是第三人称
	GameView = EGameViewMode::Third;

	//给方向赋值
	Direction = 0.f;
	//给是否在空中赋值
	IsInAir = false;
}

void USlAiThirdPlayerAnim::UpdateParameter()
{
	Super::UpdateParameter();
	//如果不存在直接返回，避免空指针产生中断
	if (!SPCharacter) return;
	//获得是否在跳跃
	IsInAir = SPCharacter->GetCharacterMovement()->IsFalling();
	//速度朝向的Yaw旋转减去Actor朝向其实就是摄像机朝向的Yaw旋转得到相对的方向
	float PreDir = SPCharacter->GetVelocity().ToOrientationRotator().Yaw - SPCharacter->GetActorRotation().Yaw;

#if 0
	//输出数据帮助理解欧拉角
	//速度朝向
	SlAiHelper::Debug(FString("SPCharacter->Velocity:") + FString::SanitizeFloat(SPCharacter->GetVelocity().ToOrientationRotator().Yaw),0.f);
	//人物朝向
	SlAiHelper::Debug(FString("SPCharacter:") + FString::SanitizeFloat(SPCharacter->GetActorRotation().Yaw),0.f);
	//摄像机朝向（速度跟人物朝向的夹角）
	SlAiHelper::Debug(FString("PreDir:") + FString::SanitizeFloat(PreDir), 0.f);
#endif

	//如果这里想不明白可以去玩点乘思路清晰一些
	if (PreDir > 180.f) PreDir -= 360.f;
	if (PreDir < -180.f) PreDir += 360.f;
	Direction = PreDir;
#if 0
	SlAiHelper::Debug(FString("Direction:") + FString::SanitizeFloat(Direction), 0.f);
#endif
}
