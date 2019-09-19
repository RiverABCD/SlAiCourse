// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlAiFlobObject.generated.h"

UCLASS()
class SLAICOURSE_API ASlAiFlobObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlAiFlobObject();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//初始化生成掉落物
	void CreateFlobObject(int ObjectID);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	//渲染贴图
	void RenderTexture();
	//动态检测事件
	void DetectPlayer();
	//销毁事件
	void DestroyEvent();
private:
	class UBoxComponent* BoxCollision;

	class UStaticMeshComponent* BaseMesh;
	//物品ID
	int ObjectIndex;
	
	class UTexture* ObjectIconTex;

	class UMaterialInstanceDynamic* ObjectIconMatDynamic;

	//玩家指针
	class ASlAiPlayerCharacter* SPCharacter;
	//动态检测Timer
	FTimerHandle DetectTimer;
	//销毁Timer
	FTimerHandle DestroyTimer;
};
