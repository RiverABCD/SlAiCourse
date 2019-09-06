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

	//�ṩ��ShortcutWidget����ӿ��������ί��
	void RegisterShortcutContainer(TArray<TSharedPtr<ShortcutContainer>>* ContainerList, TSharedPtr<STextBlock> ShortcutInfoTextBlock);

	//�л������
	void ChooseShortcut(bool IsPre);
	//��ȡѡ�������ڵ���Ʒ��Index
	int GetCurrentHandObjectIndex() const;

	//��ȡ��ǰ�ֳ���Ʒ����Ʒ����
	EObjectType::Type GetCurrentObjectType();
public:
	//��ǰ��ѡ�еĿ�������
	int CurrentShortcutIndex;
private:
	//��ȡ�������Ʒ��Ϣ
	FText GetShortcutInfoText() const;

private:
	//���������
	TArray<TSharedPtr<ShortcutContainer>> ShortcutContainerList;
	
	//�������Ϣ����
	TAttribute<FText> ShortcutInfoTextAttr;
};
