// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiPlayerState.h"
#include "STextBlock.h"
#include "SlAiDataHandle.h"


ASlAiPlayerState::ASlAiPlayerState()
{
	//��ǰѡ�еĿ�������
	CurrentShortcutIndex = 0;
}
void ASlAiPlayerState::RegisterShortcutContainer(TArray<TSharedPtr<ShortcutContainer>>* ContainerList, TSharedPtr<STextBlock> ShortcutInfoTextBlock)
{
	for (TArray<TSharedPtr<ShortcutContainer>>::TIterator It(*ContainerList); It; ++It)
	{
		ShortcutContainerList.Add(*It);
	}
	ShortcutInfoTextAttr.BindUObject(this, &ASlAiPlayerState::GetShortcutInfoText);
	//�󶨿������ϢTextBlock
	ShortcutInfoTextBlock->SetText(ShortcutInfoTextAttr);

	//��ʱ���Դ���,���ÿ��������Ʒ
	ShortcutContainerList[1]->SetObject(1)->SetObjectNum(5);
	ShortcutContainerList[2]->SetObject(2)->SetObjectNum(15);
	ShortcutContainerList[3]->SetObject(3)->SetObjectNum(1);
	ShortcutContainerList[4]->SetObject(4)->SetObjectNum(35);
	ShortcutContainerList[5]->SetObject(5)->SetObjectNum(45);
	ShortcutContainerList[6]->SetObject(6)->SetObjectNum(55);
	ShortcutContainerList[7]->SetObject(7)->SetObjectNum(64);
}

void ASlAiPlayerState::ChooseShortcut(bool IsPre)
{
	//��һ����ѡ����������±�
	int NextIndex = 0;
	if (IsPre)
	{
		NextIndex = CurrentShortcutIndex - 1 < 0 ? 8 : CurrentShortcutIndex - 1;
	} 
	else
	{
		NextIndex = CurrentShortcutIndex + 1 > 8 ? 0 : CurrentShortcutIndex + 1;
	}
	ShortcutContainerList[CurrentShortcutIndex]->SetChoosed(false);
	ShortcutContainerList[NextIndex]->SetChoosed(true);
	//���µ�ǰѡ�������Index
	CurrentShortcutIndex = NextIndex;
}

int ASlAiPlayerState::GetCurrentHandObjectIndex() const
{
	if (ShortcutContainerList.Num() == 0) return 0;
	return ShortcutContainerList[CurrentShortcutIndex]->ObjectIndex;
}

FText ASlAiPlayerState::GetShortcutInfoText() const
{
	TSharedPtr<ObjectAttribute> ObjectAttr;
	ObjectAttr = *SlAiDataHandle::Get()->ObjectAttrMap.Find(GetCurrentHandObjectIndex());
	switch (SlAiDataHandle::Get()->CurrentCulture)
	{
	case ECultureTeam::EN:
		return ObjectAttr->EN;
	case ECultureTeam::ZH:
		return ObjectAttr->ZH;
	}
	return ObjectAttr->ZH;
}
