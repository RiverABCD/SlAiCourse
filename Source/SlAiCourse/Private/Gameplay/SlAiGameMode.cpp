﻿// Fill out your copyright notice in the Description page of Project Settings.

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
#include "SlAiSceneCapture2D.h"

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
	//小地图还没生成
	IsCreateMiniMap = false;
}

void ASlAiGameMode::Tick(float DeltaSeconds)
{	//初始化背包
	InitializePackage();
	//实时更新小地图
	InitializeMiniMapCamera();
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

void ASlAiGameMode::InitializeMiniMapCamera()
{
	//如果摄像机还不存在并且世界已经存在
	if (!IsCreateMiniMap && GetWorld())
	{
		//生成小地图摄像机
		MiniMapCamera = GetWorld()->SpawnActor<ASlAiSceneCapture2D>(ASlAiSceneCapture2D::StaticClass());
		//运行委托给MiniMapWidget传递渲染的MiniMapTex
		RegisterMiniMap.ExecuteIfBound(MiniMapCamera->GetMiniMapTex());
		//设置已经生成小地图
		IsCreateMiniMap = true;
	}
	//如果小地图已经创建
	if (IsCreateMiniMap)
	{
		//每帧更新小地图摄像机的位置和旋转
		MiniMapCamera->UpdateTransform(SPCharacter->GetActorLocation(), SPCharacter->GetActorRotation());
	}
}
