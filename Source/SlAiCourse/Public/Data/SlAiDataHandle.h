// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlAiTypes.h"

class USoundCue;
/**
 * 
 */
class SLAICOURSE_API SlAiDataHandle
{
public:
	SlAiDataHandle();
	static void Initialize();
	static TSharedPtr<SlAiDataHandle> Get();
	//�޸���Ӣ��
	void ChangeLocalizationCulture(ECultureTeam Culture);
	//�޸Ĳ˵�����
	void ResetMenuVolume(float MusicVol, float SoundVol);
	//��Ϸ���ݳ�ʼ��
	void InitializeGameData();

public:
	//����
	ECultureTeam CurrentCulture;
	//����
	float MusicVolume;
	float SoundVolume;
	//�浵����
	TArray<FString> RecordDataList;
	//�浵��
	FString RecordName;
	//��Ʒ����ͼ
	TMap<int, TSharedPtr<ObjectAttribute>> ObjectAttrMap;
	//��Ʒ��ͼ��Դ����
	TArray<const FSlateBrush*> ObjectBrushList;
	//��Դ����ͼ
	TMap<int, TSharedPtr<ResourceAttribute>> ResourceAttrMap;
private:
	//��������
	static TSharedRef<SlAiDataHandle> Create();
	//����Enum���ͻ�ȡ�ַ���
	template <typename TEnum>
	FString GetEnumValueAsString(const FString& name,TEnum Value);
	//�����ַ�����ȡEnumֵ
	template <typename TEnum>
	TEnum GetEnumValueFromString(const FString& name, FString Value);

	//��ʼ���浵����
	void InitRecordData();
	//��ʼ��Menu��������
	void InitializedMenuAudio();
	//��ʼ����Ʒ����ͼ
	void InitObjectAttr();
	//��ʼ����Դ����ͼ
	void InitResourceAttrMap();
	//��ʼ���ϳɱ�ͼ
	//void InitCompoundTableMap();
	//��ʼ��Game��������
	//void InitializeGameAudio();

private:
	static TSharedPtr<SlAiDataHandle> DataInstance;
	//����Menu������
	TMap<FString, TArray<USoundCue*>> MenuAudioResource;
	//��ȡMenuStyle,�������������ļ�
	const struct FSlAiMenuStyle* MenuStyle;
	//��ȡGameStyle
	const struct FSlAiGameStyle* GameStyle;
	//�������
	class USoundMix* SlAiSoundMix;
	class USoundClass* SlAiMusicClass;
	USoundClass* SlAiSoundClass;
	class FAudioDevice* AudioDevice;

};


