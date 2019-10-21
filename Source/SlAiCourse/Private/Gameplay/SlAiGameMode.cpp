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
#include "SlAiSceneCapture2D.h"
#include "SlAiEnemyCharacter.h"
#include "EngineUtils.h"
#include "Sound/SoundWave.h"
#include "SlAiSaveGame.h"
#include "SlAiResourceRock.h"
#include "SlAiResourceTree.h"
#include "SlAiPickupStone.h"
#include "SlAiPickupWood.h"

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
	//开始设置不需要加载存档
	IsNeedLoadRecord = false;
}

void ASlAiGameMode::Tick(float DeltaSeconds)
{	
	//给背包加载存档,放在初始化背包上面是为了在第二帧再执行，因为第一帧这里函数开头有个判断，直接return了
	//到InitializePackage();的时候才会将IsInitPackage设置true,这时第二帧回来再执行LoadRecordPackage();
	LoadRecordPackage();
	//初始化背包
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

	//播放背景音乐
	USoundWave* BGMusic = LoadObject<USoundWave>(NULL, TEXT("SoundWave'/Game/Res/Sound/GameSound/GameBG.GameBG'"));
	BGMusic->bLooping = true;
	UGameplayStatics::PlaySound2D(GetWorld(),BGMusic,0.2f);

	LoadRecord();
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
		//绑定修改小地图视野的委托
		SPController->UpdateMiniMapWidth.BindUObject(MiniMapCamera, &ASlAiSceneCapture2D::UpdateMiniMapWidth);
		//设置已经生成小地图
		IsCreateMiniMap = true;
	}
	//如果小地图已经创建
	if (IsCreateMiniMap)
	{
		//每帧更新小地图摄像机的位置和旋转
		MiniMapCamera->UpdateTransform(SPCharacter->GetActorLocation(), SPCharacter->GetActorRotation());

		TArray<FVector2D> EnemyPosList;
		TArray<bool> EnemyLockList;
		TArray<float> EnemyRotateList;

		//获取场景中的敌人
		for (TActorIterator<ASlAiEnemyCharacter> EnemyIt(GetWorld()); EnemyIt; ++EnemyIt)
		{
			FVector EnemyPos = FVector((*EnemyIt)->GetActorLocation().X - SPCharacter->GetActorLocation().X, (*EnemyIt)->GetActorLocation().Y - SPCharacter->GetActorLocation().Y,0.f);
			EnemyPos = FQuat(FVector::UpVector, FMath::DegreesToRadians(-SPCharacter->GetActorRotation().Yaw - 90.f))*EnemyPos;
			EnemyPosList.Add(FVector2D(EnemyPos.X, EnemyPos.Y));

			EnemyLockList.Add((*EnemyIt)->IsLockPlayer());
			EnemyRotateList.Add((*EnemyIt)->GetActorRotation().Yaw - SPCharacter->GetActorRotation().Yaw);
		}

		//每帧更新小地图的方向文字位置
		UpdateMapData.ExecuteIfBound(SPCharacter->GetActorRotation(), MiniMapCamera->GetMapSize(), &EnemyPosList, &EnemyLockList, &EnemyRotateList);

	}
}

void ASlAiGameMode::LoadRecord()
{
	//如果RecordName为空,直接renturn
	if (SlAiDataHandle::Get()->RecordName.IsEmpty() || SlAiDataHandle::Get()->RecordName.Equals(FString("Default"))) return;
	//循环检测存档是否已经存在
	for (TArray<FString>::TIterator It(SlAiDataHandle::Get()->RecordDataList); It; ++It) {
		//如果有一个一样就直接设置为true,并且直接跳出循环
		if ((*It).Equals(SlAiDataHandle::Get()->RecordName)) {
			IsNeedLoadRecord = true;
			break;
		}
	}
	//如果需要加载,进行存档的加载,如果存档存在,进行加载
	if (IsNeedLoadRecord && UGameplayStatics::DoesSaveGameExist(SlAiDataHandle::Get()->RecordName, 0))
	{
		GameRecord = Cast<USlAiSaveGame>(UGameplayStatics::LoadGameFromSlot(SlAiDataHandle::Get()->RecordName, 0));
	}
	else {
		IsNeedLoadRecord = false;
	}

	//如果需要加载并且存档存在
	if (IsNeedLoadRecord && GameRecord)
	{
		//设置玩家位置和血量
		SPCharacter->SetActorLocation(GameRecord->PlayerLocation);
		SPState->LoadState(GameRecord->PlayerHP, GameRecord->PlayerHunger);

		//循环设置敌人
		int EnemyCount = 0;
		for (TActorIterator<ASlAiEnemyCharacter> EnemyIt(GetWorld()); EnemyIt; ++EnemyIt) {
			if (EnemyCount < GameRecord->EnemyLoaction.Num())
			{
				(*EnemyIt)->SetActorLocation(GameRecord->EnemyLoaction[EnemyCount]);
				(*EnemyIt)->LoadHP(GameRecord->EnemyHP[EnemyCount]);
			}
			else {
				//告诉这个敌人下一帧销毁
				(*EnemyIt)->IsDestroyNextTick = true;
			}
			++EnemyCount;
		}

		//循环设置岩石
		int RockCount = 0;
		for (TActorIterator<ASlAiResourceRock> RockIt(GetWorld()); RockIt; ++RockIt) {
			if (RockCount < GameRecord->ResourceRock.Num()) {
				(*RockIt)->SetActorLocation(GameRecord->ResourceRock[RockCount]);
			}
			else {
				//告诉这个资源下一帧销毁
				(*RockIt)->IsDestroyNextTick = true;
			}
			++RockCount;
		}

		//循环设置树木
		int TreeCount = 0;
		for (TActorIterator<ASlAiResourceTree> TreeIt(GetWorld()); TreeIt; ++TreeIt) {
			if (TreeCount < GameRecord->ResourceTree.Num()) {
				(*TreeIt)->SetActorLocation(GameRecord->ResourceTree[TreeCount]);
			}
			else {
				//告诉这个资源下一帧销毁
				(*TreeIt)->IsDestroyNextTick = true;
			}
			++TreeCount;
		}

		//循环设置拾取物品石头
		int StoneCount = 0;
		for (TActorIterator<ASlAiPickupStone> StoneIt(GetWorld()); StoneIt; ++StoneIt) {
			if (StoneCount < GameRecord->PickupStone.Num()) {
				(*StoneIt)->SetActorLocation(GameRecord->PickupStone[StoneCount]);
			}
			else {
				//告诉这个资源下一帧销毁
				(*StoneIt)->IsDestroyNextTick = true;
			}
			++StoneCount;
		}

		//循环设置拾取物品木头
		int WoodCount = 0;
		for (TActorIterator<ASlAiPickupWood> WoodIt(GetWorld()); WoodIt; ++WoodIt) {
			if (WoodCount < GameRecord->PickupWood.Num()) {
				(*WoodIt)->SetActorLocation(GameRecord->PickupWood[WoodCount]);
			}
			else {
				//告诉这个资源下一帧销毁
				(*WoodIt)->IsDestroyNextTick = true;
			}
			++WoodCount;
		}
	}

}

void ASlAiGameMode::LoadRecordPackage()
{
	//如果背包没有初始化或者不用加载存档,直接返回
	if (!IsInitPackage || !IsNeedLoadRecord) return;

	if (IsNeedLoadRecord && GameRecord)
	{
		SlAiPackageManager::Get()->LoadRecord(&GameRecord->InputIndex, &GameRecord->InputNum, &GameRecord->NormalIndex, &GameRecord->NormalNum, &GameRecord->ShortcutIndex, &GameRecord->ShortcutNum);
	}
	//最后设置不用加载存档了
	IsNeedLoadRecord = false;

}

void ASlAiGameMode::SaveGame()
{
	//如果存档名是Default,不进行保存
	if (SlAiDataHandle::Get()->RecordName.Equals(FString("Default"))) return;

	//创建一个新的存档
	USlAiSaveGame* NewRecord = Cast<USlAiSaveGame>(UGameplayStatics::CreateSaveGameObject(USlAiSaveGame::StaticClass()));

	//对存档进行赋值
	//设置玩家位置和血量
	NewRecord->PlayerLocation = SPCharacter->GetActorLocation();
	SPState->SaveState(NewRecord->PlayerHP, NewRecord->PlayerHunger);

	//循环设置敌人
	for (TActorIterator<ASlAiEnemyCharacter> EnemyIt(GetWorld()); EnemyIt; ++EnemyIt)
	{
		NewRecord->EnemyLoaction.Add((*EnemyIt)->GetActorLocation());
		NewRecord->EnemyHP.Add((*EnemyIt)->GetHP());
	}

	//循环设置岩石
	for (TActorIterator<ASlAiResourceRock> RockIt(GetWorld()); RockIt; ++RockIt)
	{
		NewRecord->ResourceRock.Add((*RockIt)->GetActorLocation());
	}

	//循环设置树木
	for (TActorIterator<ASlAiResourceTree> TreeIt(GetWorld()); TreeIt; ++TreeIt) {
		NewRecord->ResourceTree.Add((*TreeIt)->GetActorLocation());
	}

	//循环设置拾取物品石头
	for (TActorIterator<ASlAiPickupStone> StoneIt(GetWorld()); StoneIt; ++StoneIt) {
		NewRecord->PickupStone.Add((*StoneIt)->GetActorLocation());
	}

	//循环设置拾取物品木头
	for (TActorIterator<ASlAiPickupWood> WoodIt(GetWorld()); WoodIt; ++WoodIt) {
		NewRecord->PickupWood.Add((*WoodIt)->GetActorLocation());
	}

	//获取背包数据
	SlAiPackageManager::Get()->SaveData(NewRecord->InputIndex, NewRecord->InputNum, NewRecord->NormalIndex, NewRecord->NormalNum, NewRecord->ShortcutIndex, NewRecord->ShortcutNum);

	//查看是否已经有存档存在
	if (UGameplayStatics::DoesSaveGameExist(SlAiDataHandle::Get()->RecordName, 0)) {
		//有的话先删除
		UGameplayStatics::DeleteGameInSlot(SlAiDataHandle::Get()->RecordName, 0);
	}
	//保存存档
	UGameplayStatics::SaveGameToSlot(NewRecord, SlAiDataHandle::Get()->RecordName, 0);

	//查看json是否已经有这个存档
	bool IsRecordExist = false;
	for (TArray<FString>::TIterator It(SlAiDataHandle::Get()->RecordDataList); It; ++It)
	{
		//只要有一个相同,就跳出
		if ((*It).Equals(SlAiDataHandle::Get()->RecordName)) {
			IsRecordExist = true;
			break;
		}
	}
	//如果存档不存在,让数据管理类添加存档到json
	if (!IsRecordExist) SlAiDataHandle::Get()->AddNewRecord();
}