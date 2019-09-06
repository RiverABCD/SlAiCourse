// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiHandWood.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"

ASlAiHandWood::ASlAiHandWood() :Super()
{
	//给模型组件添加上模型
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_TreeLog_01.SM_Env_TreeLog_01'"));
	//绑定模型到Mesh组件
	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);

	BaseMesh->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	BaseMesh->SetRelativeRotation(FRotator(0.f, -20.f, 0.f));

	AffectCollision->SetBoxExtent(FVector(10.f, 10.f, 10.f));
	AffectCollision->SetRelativeLocation(FVector(0.f, 0.f, 10.f));
}
//在这里实例化组件是因为要等DataHandle在构造函数把数据信息加载完毕
void ASlAiHandWood::BeginPlay()
{
	Super::BeginPlay();

	//定义物品序号
	ObjectIndex = 1;
}
