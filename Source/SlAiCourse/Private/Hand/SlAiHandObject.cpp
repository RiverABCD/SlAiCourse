// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiHandObject.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "ConstructorHelpers.h"

//手持物品类
#include "SlAiHandNone.h"
#include "SlAiHandWood.h"
#include "SlAiHandStone.h"
#include "SlAiHandApple.h"
#include "SlAiHandMeat.h"
#include "SlAiHandAxe.h"
#include "SlAiHandHammer.h"
#include "SlAiHandSword.h"

#include "SlAiHelper.h"

// Sets default values
ASlAiHandObject::ASlAiHandObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//实例化根组件
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;
	
	//实例化BashMesh
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BashMesh"));
	BaseMesh->SetupAttachment(RootComponent);
	BaseMesh->SetCollisionProfileName(TEXT("NoCollision"));

	//实例化碰撞
	AffectCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("AffectCollision"));
	AffectCollision->SetupAttachment(RootComponent);
	AffectCollision->SetCollisionProfileName(TEXT("ToolProfile"));

	//初始时关闭Overlay检测
	AffectCollision->bGenerateOverlapEvents = false;

	//绑定检测方法到碰撞体
	FScriptDelegate OverlayBegin;
	OverlayBegin.BindUFunction(this, "OnOverlayBegin");
	AffectCollision->OnComponentBeginOverlap.Add(OverlayBegin);

	FScriptDelegate OverlayEnd;
	OverlayEnd.BindUFunction(this, "OnOverlayEnd");
	AffectCollision->OnComponentEndOverlap.Add(OverlayEnd);
}

// Called when the game starts or when spawned
void ASlAiHandObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASlAiHandObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TSubclassOf<AActor> ASlAiHandObject::SpawnHandObject(int ObjectID)
{
	switch (ObjectID)
	{
	case 0:
		return ASlAiHandNone::StaticClass();
	case 1:
		return ASlAiHandWood::StaticClass();
	case 2:
		return ASlAiHandStone::StaticClass();
	case 3:
		return ASlAiHandApple::StaticClass();
	case 4:
		return ASlAiHandMeat::StaticClass();
	case 5:
		return ASlAiHandAxe::StaticClass();
	case 6:
		return ASlAiHandHammer::StaticClass();
	case 7:
		return ASlAiHandSword::StaticClass();
	}

	return ASlAiHandNone::StaticClass();
}

void ASlAiHandObject::ChangeOverlayDetect(bool IsOpen)
{
	AffectCollision->bGenerateOverlapEvents = IsOpen;
}

void ASlAiHandObject::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	SlAiHelper::Debug(FString("OnOverlayBegin"), 3.f);
}

void ASlAiHandObject::OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	SlAiHelper::Debug(FString("OnOverlayEnd"), 3.f);
}


