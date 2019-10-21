// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiPickupObject.h"
#include "Components/StaticMeshComponent.h"
#include "SlAiTypes.h"
#include "SlAiDataHandle.h"
#include "Engine/GameEngine.h"

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

	//设置下一帧不销毁自己
	IsDestroyNextTick = false;
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
	//如果下一帧要销毁，执行销毁
	if (IsDestroyNextTick) GetWorld()->DestroyActor(this);
}

FText ASlAiPickupObject::GetInfoText() const
{
	TSharedPtr<ObjectAttribute> ObjectAttr = *SlAiDataHandle::Get()->ObjectAttrMap.Find(ObjectIndex);
	switch (SlAiDataHandle::Get()->CurrentCulture)
	{
	case ECultureTeam::EN:
		return ObjectAttr->EN;
	case ECultureTeam::ZH:
		return ObjectAttr->ZH;
	}
	return ObjectAttr->ZH;
}

int ASlAiPickupObject::TakePickup()
{
	BaseMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	if (GetWorld()) GetWorld()->DestroyActor(this);
	return ObjectIndex;
}

