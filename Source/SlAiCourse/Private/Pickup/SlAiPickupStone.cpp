// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiPickupStone.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/StaticMesh.h"


ASlAiPickupStone::ASlAiPickupStone()
{
	////给模型组件添加上模型
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Prop_StoneBlock_01.SM_Prop_StoneBlock_01'"));
	//绑定模型到Mesh组件
	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);
	BaseMesh->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.5f));

	ObjectIndex = 2;
}
