// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
public:
	//��ԴID
	int ResourceIndex;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	//�����
	USceneComponent* RootScene;
	//��̬ģ��
	UStaticMeshComponent* BaseMesh;
	//������Դ��ַ���������ˢ��Դ
	TArray<FString> ResourcePath;
	
	
};
