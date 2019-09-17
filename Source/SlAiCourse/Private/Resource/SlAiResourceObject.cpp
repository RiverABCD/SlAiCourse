// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiResourceObject.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/GameEngine.h"
#include "SlAiDataHandle.h"
#include "SlAiFlobObject.h"

// Sets default values
ASlAiResourceObject::ASlAiResourceObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//实例化根节点
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	//实例化模型组件
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);
	BaseMesh->SetCollisionProfileName(FName("ResourceProfile"));

	//开启交互检测
	BaseMesh->bGenerateOverlapEvents = true;
	//BaseMesh->SetGenerateOverlapEvents(true);
	//设置在下一帧不销毁

	
}

// Called when the game starts or when spawned
void ASlAiResourceObject::BeginPlay()
{
	Super::BeginPlay();
	//这段有问题
	
	//TSharedPtr<ResourceAttribute> ResourceAttr = *SlAiDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);
	//HP = BaseHP = ResourceAttr->HP;
	
}

// Called every frame
void ASlAiResourceObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASlAiResourceObject::CreateFlobObject()
{
	TSharedPtr<ResourceAttribute> ResourceAttr = *SlAiDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);
	//遍历生成掉落物
	for (TArray<TArray<int>>::TIterator It(ResourceAttr->FlobObjectInfo); It; ++It) {
		//随机生成的数量
		FRandomStream Stream;
		Stream.GenerateNewSeed();
		//生成数量 "FlobObjectInfo": [{"0":    "2_3,6"},],下面的(*It)[1], (*It)[2],(*It)[0], 对应的就是其中的"2_3,6"
		int Num = Stream.RandRange((*It)[1], (*It)[2]);

		if (GetWorld()) {
			for (int i = 0; i < Num; ++i) {
				//生成掉落物
				ASlAiFlobObject* FlobObject = GetWorld()->SpawnActor<ASlAiFlobObject>(GetActorLocation() + FVector(0.f, 0.f, 20.f), FRotator::ZeroRotator);
				FlobObject->CreateFlobObject((*It)[0]);
			}
		}
	}
}

FText ASlAiResourceObject::GetInfoText() const
{
	TSharedPtr<ResourceAttribute> ResourceAttr = *SlAiDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);
	switch (SlAiDataHandle::Get()->CurrentCulture)
	{
	case ECultureTeam::EN:
		return ResourceAttr->EN;
		break;
	case ECultureTeam::ZH:
		return ResourceAttr->ZH;
		break;
	}
	return ResourceAttr->ZH;
}


EResourceType::Type ASlAiResourceObject::GetResourceType()
{
	TSharedPtr<ResourceAttribute> ResourceAttr = *SlAiDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);
	return ResourceAttr->ResourceType;
}

float ASlAiResourceObject::GetHPRange()
{
	return FMath::Clamp<float>((float)HP/(float)BaseHP,0.f,1.f);
}

ASlAiResourceObject * ASlAiResourceObject::TakeObjectDamage(int Damage)
{
	HP = FMath::Clamp<int>(HP - Damage, 0, BaseHP);
	if (HP <= 0) {
		//检测失败
		BaseMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
		//创建掉落物
		CreateFlobObject();
		//销毁物体
		GetWorld()->DestroyActor(this);
	}
	return this;
}

