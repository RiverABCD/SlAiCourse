// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlAiPickupObject.generated.h"

UCLASS()
class SLAICOURSE_API ASlAiPickupObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlAiPickupObject();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	int ObjectIndex;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	//根节点
	USceneComponent* RootScene;
	//静态模型
	UStaticMeshComponent* BaseMesh;
};
