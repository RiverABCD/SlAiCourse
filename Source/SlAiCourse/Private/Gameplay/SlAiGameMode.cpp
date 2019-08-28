// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiGameMode.h"
#include "SlAiPlayerController.h"
#include "SlAiPlayerCharacter.h"
#include "SlAiPlayerState.h"
#include "SlAiGameHUD.h"

#include "SlAiDataHandle.h"
#include "SlAiHelper.h"

#include "SlAiGameInstance.h"
#include "Kismet/GameplayStatics.h"

ASlAiGameMode::ASlAiGameMode()
{
	//允许开启帧函数
	PrimaryActorTick.bCanEverTick = true;
	//添加组件
	HUDClass = ASlAiGameHUD::StaticClass();
	PlayerControllerClass = ASlAiPlayerController::StaticClass();
	PlayerStateClass = ASlAiPlayerState::StaticClass();
	DefaultPawnClass = ASlAiPlayerCharacter::StaticClass();
}

void ASlAiGameMode::Tick(float DeltaSeconds)
{

}

void ASlAiGameMode::InitGamePlayModule()
{
	//添加引用
	SPController = Cast<ASlAiPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	SPCharacter = Cast<ASlAiPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	SPState = Cast<ASlAiPlayerState>(SPController->PlayerState);
}

void ASlAiGameMode::BeginPlay()
{
	//初始化游戏数据
	SlAiDataHandle::Get()->InitializeGameData();
	
	if(!SPController) InitGamePlayModule();
}
