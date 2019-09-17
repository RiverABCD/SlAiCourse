// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlAiTypes.h"
#include "SlAiResourceObject.generated.h"

UCLASS()
class SLAICOURSE_API ASlAiResourceObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlAiResourceObject();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//获取物品信息
	FText GetInfoText() const;
#if 1
	//获取资源类型
	EResourceType::Type GetResourceType();
	//获取血量百分比
	float GetHPRange();
	//获取伤害
	ASlAiResourceObject* TakeObjectDamage(int Damage);
#endif
public:
	//资源ID
	int ResourceIndex;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//生成凋落物
	void CreateFlobObject();
protected:
	//根组件
	USceneComponent* RootScene;
	//静态模型
	UStaticMeshComponent* BaseMesh;
	//保存资源地址，用于随机刷资源
	TArray<FString> ResourcePath;
	//血量
	int HP;
	//基础血量
	int BaseHP;
	
};
