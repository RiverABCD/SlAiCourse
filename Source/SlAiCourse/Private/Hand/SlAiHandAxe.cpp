// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiHandAxe.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"

ASlAiHandAxe::ASlAiHandAxe()
{
	//给模型组件添加模型
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Wep_Axe_01.SM_Wep_Axe_01'"));
	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);

	BaseMesh->SetRelativeLocation(FVector(-28.f, -4.9f, 3.23f));
	BaseMesh->SetRelativeRotation(FRotator(0.f, -90.f, 90.f));
	BaseMesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));

	//设置碰撞体属性
	AffectCollision->SetRelativeLocation(FVector(32.f, -5.f, 3.f));
	AffectCollision->SetRelativeScale3D(FVector(0.375f, 0.5f, 0.125f));

}

void ASlAiHandAxe::BeginPlay()
{
	Super::BeginPlay();
	//定义物品序号
	ObjectIndex = 5;
}
