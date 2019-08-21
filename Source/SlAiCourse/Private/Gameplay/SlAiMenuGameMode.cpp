// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiMenuGameMode.h"
#include "SlAiMenuController.h"
#include "SlAiMenuHUD.h"

#include "SlAiGameInstance.h"
#include "Kismet/GameplayStatics.h"


ASlAiMenuGameMode::ASlAiMenuGameMode()
{
	//绑定相关类，对应编辑器中WorldSetting中GameMode下相关绑定
	HUDClass = ASlAiMenuHUD::StaticClass();
	PlayerControllerClass = ASlAiMenuController::StaticClass();
}

void ASlAiMenuGameMode::BeginPlay()
{
	Cast<USlAiGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GameName = FString("SlAiCourse");
}
