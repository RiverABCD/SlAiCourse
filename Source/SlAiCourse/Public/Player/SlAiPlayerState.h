// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SlAiTypes.h"
#include "SlAiPlayerState.generated.h"

class STextBlock;
/**
 * 
 */
UCLASS()
class SLAICOURSE_API ASlAiPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ASlAiPlayerState();

	//提供给ShortcutWidget的添加快捷栏容器委托
	void RegisterShortcutContainer(TArray<TSharedPtr<ShortcutContainer>>* ContainerList, TSharedPtr<STextBlock> ShortcutInfoTextBlock);

	//切换快捷栏
	void ChooseShortcut(bool IsPre);
	//获取选中容器内的物品的Index
	int GetCurrentHandObjectIndex() const;

	//获取当前手持物品的物品类型
	EObjectType::Type GetCurrentObjectType();
public:
	//当前被选中的快捷栏序号
	int CurrentShortcutIndex;
private:
	//获取快捷栏物品信息
	FText GetShortcutInfoText() const;

private:
	//快捷栏序列
	TArray<TSharedPtr<ShortcutContainer>> ShortcutContainerList;
	
	//快捷栏信息参数
	TAttribute<FText> ShortcutInfoTextAttr;
};
