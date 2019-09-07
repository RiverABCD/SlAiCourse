// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiPickupObject.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASlAiPickupObject::ASlAiPickupObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//实例化根节点
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	//在这里实现模型组件但是不进行模型绑定
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);
	////设置模型碰撞为PickupProfile
	BaseMesh->SetCollisionProfileName(FName("PickupProfile"));

}

// Called when the game starts or when spawned
void ASlAiPickupObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASlAiPickupObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

