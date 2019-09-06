// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiResourceTree.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/StaticMesh.h"



ASlAiResourceTree::ASlAiResourceTree()
{
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_Tree_07.SM_Env_Tree_07'"));
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_Tree_016.SM_Env_Tree_016'"));
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_Tree_014_Snow.SM_Env_Tree_014_Snow'"));
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_Tree_012.SM_Env_Tree_012'"));
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_TreePine_01_Snow.SM_Env_TreePine_01_Snow'"));
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_Tree_01_Snow.SM_Env_Tree_01_Snow'"));
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_Tree_06_Snow.SM_Env_Tree_06_Snow'"));
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_TreeDead_02_Snow.SM_Env_TreeDead_02_Snow'"));
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_TreeDead_01.SM_Env_TreeDead_01'"));
	ResourcePath.Add(FString("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_Tree_012_Snow.SM_Env_Tree_012_Snow'"));

	FRandomStream Stream;
	//产生随机种子
	Stream.GenerateNewSeed();
	int RandIndex = Stream.RandRange(0, ResourcePath.Num() - 1);
	//给模型组件添加上模型,这里不能用静态变量
	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(*ResourcePath[RandIndex]);
	//绑定模型到Mesh组件
	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);

	ResourceIndex = 1;
}
