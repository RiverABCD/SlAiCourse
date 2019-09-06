// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiHandHammer.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"

ASlAiHandHammer::ASlAiHandHammer()
{
	//给模型组件添加上模型
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Bld_FencePost_01.SM_Bld_FencePost_01'"));
	//绑定模型到Mesh组件
	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);

	//添加扩展模型组件
	ExtendMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ExtendMesh"));
	ExtendMesh->SetupAttachment(RootComponent);
	ExtendMesh->SetCollisionProfileName(FName("NoCollision"));

	//绑定模型到扩展模型组件
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticExtendMesh(TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Prop_StoneBlock_01.SM_Prop_StoneBlock_01'"));
	//绑定模型到Mesh组件
	ExtendMesh->SetStaticMesh(StaticExtendMesh.Object);


	BaseMesh->SetRelativeLocation(FVector(35.f, 0.f, 3.f));
	BaseMesh->SetRelativeRotation(FRotator(0.f, -90.f, -90.f));
	BaseMesh->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));

	ExtendMesh->SetRelativeLocation(FVector(33.f, 1.f, 3.f));
	ExtendMesh->SetRelativeRotation(FRotator(0.f, -90.f, -90.f));
	ExtendMesh->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));


	//设置碰撞体属性
	AffectCollision->SetRelativeLocation(FVector(26.f, 1.f, 3.f));
	AffectCollision->SetRelativeScale3D(FVector(0.22f, 0.44f, 0.31f));
}
void ASlAiHandHammer::BeginPlay()
{
	Super::BeginPlay();

	//定义物品序号
	ObjectIndex = 6;


}
