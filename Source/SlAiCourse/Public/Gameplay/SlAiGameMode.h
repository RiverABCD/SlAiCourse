// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SlAiGameMode.generated.h"

//初始化背包管理类委托
DECLARE_DELEGATE(FInitPackageManager)
//注册MiniMap的贴图和材质
DECLARE_DELEGATE_OneParam(FRegisterMiniMap, class UTextureRenderTarget2D*)
//更新MiniMap的数据
DECLARE_DELEGATE_FiveParams(FUpdateMapData, const FRotator, const float, const TArray<FVector2D>*, const TArray<bool>*, const TArray<float>*)
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

	//保存游戏
	void SaveGame();
public:
	class ASlAiPlayerController* SPController;

	class ASlAiPlayerCharacter* SPCharacter;

	class ASlAiPlayerState* SPState;
	//初始化背包管理委托,绑定的方法是PackageWidget的InitPackageManager方法
	FInitPackageManager InitPackageManager;
	//定义委托,绑定的方法是MiniMapWidget的RegisterMiniMap
	FRegisterMiniMap RegisterMiniMap;
	//定义委托,用于更新小地图的方向文字位置,绑定的方法的MiniMapWidget的UpdateMapDirection
	FUpdateMapData UpdateMapData;

protected:
	virtual void BeginPlay() override;

	//初始化背包管理类
	void InitializePackage();
	
	//初始化与更新小地图摄像机
	void InitializeMiniMapCamera();

	//存档加载
	void LoadRecord();

	//给背包进行加载存档,这个函数一定要在第二帧再执行,否则快捷栏没初始化完成会崩溃
	void LoadRecordPackage();

private:

	//石否已经初始化背包
	bool IsInitPackage;

	//是否已经生成小地图摄像机
	bool IsCreateMiniMap;

	//小地图相机指针
	class ASlAiSceneCapture2D* MiniMapCamera;

	//是否需要加载存档
	bool IsNeedLoadRecord;

	//游戏存档指针
	class USlAiSaveGame* GameRecord;
};
