// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlAiEnemyTool.generated.h"

UCLASS()
class SLAICOURSE_API ASlAiEnemyTool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlAiEnemyTool();

	//是否允许检测
	void ChangeOverlayDetect(bool IsOpen);

	static TSubclassOf<AActor> SpawnEnemyWeapon();

	static TSubclassOf<AActor> SpawnEnemySheild();

protected:
	UFUNCTION()
		virtual void OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		virtual void OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:

	//根组件
	USceneComponent* RootScene;

	//静态模型
	UPROPERTY(EditAnywhere, Category = Mesh)
		UStaticMeshComponent* BaseMesh;

	//盒子碰撞体
	UPROPERTY(EditAnywhere, Category = Mesh)
		class UBoxComponent* AffectCollision;
	
};
