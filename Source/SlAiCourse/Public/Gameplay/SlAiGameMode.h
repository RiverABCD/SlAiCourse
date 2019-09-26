// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SlAiGameMode.generated.h"

DECLARE_DELEGATE(FInitPackageManager)
/**
 * 
 */
UCLASS()
class SLAICOURSE_API ASlAiGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASlAiGameMode();
	//重写帧函数
	virtual void Tick(float DeltaSeconds) override;

	//组件赋值,给GameHUD调用,避免空引用引起崩溃
	void InitGamePlayModule();
public:
	class ASlAiPlayerController* SPController;

	class ASlAiPlayerCharacter* SPCharacter;

	class ASlAiPlayerState* SPState;
	//初始化背包管理委托,绑定的方法是PackageWidget的InitPackageManager方法
	FInitPackageManager InitPackageManager;

protected:
	virtual void BeginPlay() override;

	//初始化背包管理类
	void InitializePackage();
	
private:

	//石否已经初始化背包
	bool IsInitPackage;
	
};
