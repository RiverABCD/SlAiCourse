// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiEnemyTool.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/PrimitiveComponent.h"

#include "SlAiEnemyWeapon.h"
#include "SlAiEnemyShield.h"

// Sets default values
ASlAiEnemyTool::ASlAiEnemyTool()
{
	//实例化根节点
	RootScene = CreateDefaultSubobject<USceneComponent>("RootScene");
	RootComponent = RootScene;

	//在这里实现模型组件但是不进行模型绑定
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);
	BaseMesh->SetCollisionProfileName(FName("NoCollision"));

	//实现碰撞组件
	AffectCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("AffectCollision"));
	AffectCollision->SetupAttachment(BaseMesh);
	AffectCollision->SetCollisionProfileName(FName("EnemyToolProfile"));
	//初始时关闭Overlay检测
	AffectCollision->bGenerateOverlapEvents = false;

	//绑定检测方法到碰撞体
	FScriptDelegate OverlayBegin;
	OverlayBegin.BindUFunction(this, "OnOverlayBegin");
	AffectCollision->OnComponentBeginOverlap.Add(OverlayBegin);

	FScriptDelegate OverlayEnd;
	OverlayEnd.BindUFunction(this, "OnOverlayEnd");
	AffectCollision->OnComponentEndOverlap.Add(OverlayEnd);//绑定检测方法到碰撞体

}

void ASlAiEnemyTool::ChangeOverlayDetect(bool IsOpen)
{
	AffectCollision->bGenerateOverlapEvents = IsOpen;
}

TSubclassOf<AActor> ASlAiEnemyTool::SpawnEnemyWeapon()
{
	return ASlAiEnemyWeapon::StaticClass();
}

TSubclassOf<AActor> ASlAiEnemyTool::SpawnEnemySheild()
{
	return ASlAiEnemyShield::StaticClass();
}

void ASlAiEnemyTool::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}

void ASlAiEnemyTool::OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

