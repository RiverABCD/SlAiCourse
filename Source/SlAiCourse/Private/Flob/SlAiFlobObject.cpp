// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiFlobObject.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "SlAiDataHandle.h"
#include "TimerManager.h"
#include "SlAiPlayerCharacter.h"
#include "Engine/StaticMesh.h"

// Sets default values
ASlAiFlobObject::ASlAiFlobObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = (USceneComponent*)BoxCollision;
	//设置碰撞属性
	BoxCollision->SetCollisionProfileName(FName("FlobProfile"));
	//启动物体模拟
	BoxCollision->SetSimulatePhysics(true);
	//锁定旋转
	BoxCollision->SetConstraintMode(EDOFMode::Default);
	BoxCollision->GetBodyInstance()->bLockXRotation = true;
	BoxCollision->GetBodyInstance()->bLockYRotation = true;
	BoxCollision->GetBodyInstance()->bLockZRotation = true;
	//设置大小
	BoxCollision->SetBoxExtent(FVector(15.f));

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);
	BaseMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//设置变换
	BaseMesh->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	BaseMesh->SetRelativeScale3D(FVector(0.3f));

	UMaterialInterface* StaticObjectIconMat = LoadObject<UMaterialInterface>(NULL, TEXT("MaterialInstanceConstant'/Game/Material/FlobIconMatInst.FlobIconMatInst'"));
	//动态创建材质
	ObjectIconMatDynamic = UMaterialInstanceDynamic::Create(StaticObjectIconMat, nullptr);
}

// Called when the game starts or when spawned
void ASlAiFlobObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASlAiFlobObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASlAiFlobObject::RenderTexture()
{
	//ObjectIconTex如果设置在函数形参来传入的话再传入SetTextureParameterValue中可能会因为被销毁而导致传入空指针？
	TSharedPtr<ObjectAttribute> ObjectAttr = *SlAiDataHandle::Get()->ObjectAttrMap.Find(ObjectIndex);
	ObjectIconTex = LoadObject<UTexture>(NULL, *ObjectAttr->TexPath);
	ObjectIconMatDynamic->SetTextureParameterValue(FName("ObjectTex"), ObjectIconTex);
	BaseMesh->SetMaterial(0, ObjectIconMatDynamic);
}


void ASlAiFlobObject::CreateFlobObject(int ObjectID)
{
	//指定ID
	ObjectIndex = ObjectID;
	//渲染贴图
	RenderTexture();
	//物品掉落满地的形式
	//随机方向添加力
	FRandomStream Stream;
	//产生新的随机种子
	Stream.GenerateNewSeed();
	//添加偏移方向
	int DirYaw = Stream.RandRange(-180, 180);
	FRotator ForceRot = FRotator(0.f, DirYaw, 0.f);
	//添加力
	BoxCollision->AddForce((FVector(0.f, 0.f, 2.f) + ForceRot.Vector())*12000.f);
}

