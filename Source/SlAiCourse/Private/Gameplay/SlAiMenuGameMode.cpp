// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiMenuGameMode.h"
#include "SlAiMenuController.h"
#include "SlAiMenuHUD.h"



ASlAiMenuGameMode::ASlAiMenuGameMode()
{
	//������࣬��Ӧ�༭����WorldSetting��GameMode����ذ�
	HUDClass = ASlAiMenuHUD::StaticClass();
	PlayerControllerClass = ASlAiMenuController::StaticClass();
}
