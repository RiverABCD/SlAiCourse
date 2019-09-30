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
#include "SlAiPackageManager.h"

ASlAiGameMode::ASlAiGameMode()
{
	//允许开启帧函数
	PrimaryActorTick.bCanEverTick = true;
	//添加组件
	HUDClass = ASlAiGameHUD::StaticClass();
	PlayerControllerClass = ASlAiPlayerController::StaticClass();
	PlayerStateClass = ASlAiPlayerState::StaticClass();
	DefaultPawnClass = ASlAiPlayerCharacter::StaticClass();

	//开始没有初始化
	IsInitPackage = false;
}

void ASlAiGameMode::Tick(float DeltaSeconds)
{
	InitializePackage();
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

void ASlAiGameMode::InitializePackage()
{
	if (IsInitPackage) return;
	//叫PackageWidget初始化背包管理器
	InitPackageManager.ExecuteIfBound();
	//绑定丢弃物品委托
	SlAiPackageManager::Get()->PlayerThrowObject.BindUObject(SPCharacter,&ASlAiPlayerCharacter::PlayerThrowObject);
	//绑定修改快捷栏委托
	SlAiPackageManager::Get()->ChangeHandObject.BindUObject(SPState, &ASlAiPlayerState::ChangeHandObject);
	IsInitPackage = true;
}
