// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlAiTypes.h"
#include "Json.h"
/**
 * 
 */

class SLAICOURSE_API SlAiJsonHandle
{
public:
	SlAiJsonHandle();

	//�����浵����
	void RecordDataJsonRead(FString& Culture, float& MusicVolume, float& SoundVolume, TArray<FString>& RecordDataList);
	//�޸Ĵ浵
	void UpdateRecordData(FString Culture, float MusicVolume, float SoundVolume, TArray<FString>* RecordDataList);
private:
	//��ȡJson�ļ����ַ���
	bool LoadStringFromFile(const FString& FileName, const FString& RelaPath, FString& ResultString);

	//FJsonObjectת��ΪJson��ʽ���ַ���
	bool GetFStringInJsonData(const TSharedPtr<FJsonObject>& JsonObj, FString& JsonStr);

	//�����ַ������ļ�
	bool WriteFileWithJsonData(const FString& JsonStr, const FString& RelaPath, const FString& FileName);

private:
	//�浵�ļ���
	FString RecordDataFileName;

	//��Ʒ�����ļ���
	FString ObjectAttrFileName;

	//��Դ�����ļ���
	FString ResourceAttrFileName;

	//�ϳɱ��ļ���
	FString CompoundTableFileName;

	//���·��
	FString RelativePath;
};

