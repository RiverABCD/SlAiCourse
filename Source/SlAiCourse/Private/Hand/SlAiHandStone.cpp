// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiHandStone.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"

ASlAiHandStone::ASlAiHandStone()
{
	//给模型组件添加上模型
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Prop_StoneBlock_01.SM_Prop_StoneBlock_01'"));
	//绑定模型到Mesh组件
	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);

	BaseMesh->SetRelativeLocation(FVector(1.f, -1.414f, 7.071f));
	BaseMesh->SetRelativeRotation(FRotator(0.f, 0.f, -135.f));
	BaseMesh->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));

	//设置碰撞盒属性
	AffectCollision->SetBoxExtent(FVector(10.f, 10.f, 10.f));
	AffectCollision->SetRelativeLocation(FVector(0.f, 0.f, 10.f));
}

void ASlAiHandStone::BeginPlay()
{
	Super::BeginPlay();

	//定义物品序号
	ObjectIndex = 2;
}
