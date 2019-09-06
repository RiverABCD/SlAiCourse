// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiHandNone.h"
#include "Components/BoxComponent.h"

ASlAiHandNone::ASlAiHandNone()
{
	//不用绑定模型


	//设置碰撞盒属性
	AffectCollision->SetBoxExtent(FVector(10.f, 10.f, 10.f));
	AffectCollision->SetRelativeLocation(FVector(0.f, 0.f, 10.f));
}
void ASlAiHandNone::BeginPlay()
{
	Super::BeginPlay();

	//定义物品序号
	ObjectIndex = 0;
}
