// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiDataHandle.h"
#include "Internationalization.h"
#include "SlAiSingleton.h"
#include "SlAiJsonHandle.h"
#include "SlAiHelper.h"
#include "SlAiStyle.h"
#include "SlAiMenuWidgetStyle.h"
//#include "SlAiGameWidgetStyle.h"
#include "Sound/SoundCue.h"

#include "AudioDevice.h"
#include "Sound/SoundMix.h"
#include "Sound/SoundClass.h"

TSharedPtr<SlAiDataHandle> SlAiDataHandle::DataInstance = NULL;

SlAiDataHandle::SlAiDataHandle()
{
	//��ʼ���浵
	InitRecordData();
	//��ʼ����������
	InitializedMenuAudio();
}

void SlAiDataHandle::Initialize()
{
	if (!DataInstance.IsValid()) {
		DataInstance = Create();
	}
}

TSharedPtr<SlAiDataHandle> SlAiDataHandle::Get()
{
	Initialize();
	return DataInstance;
}

TSharedRef<SlAiDataHandle> SlAiDataHandle::Create()
{
	TSharedRef<SlAiDataHandle> DataRef = MakeShareable(new SlAiDataHandle());
	return DataRef;
}

void SlAiDataHandle::ChangeLocalizationCulture(ECultureTeam Culture)
{
	switch (Culture)
	{
	case ECultureTeam::EN:
		FInternationalization::Get().SetCurrentCulture(TEXT("en"));
		break;
	case ECultureTeam::ZH:
		FInternationalization::Get().SetCurrentCulture(TEXT("zh"));
		break;
	}
	//��ֵ
	CurrentCulture = Culture;
	//���´浵����
	SlAiSingleton<SlAiJsonHandle>::Get()->UpdateRecordData(GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"), CurrentCulture), MusicVolume, SoundVolume, &RecordDataList);
}

void SlAiDataHandle::ResetMenuVolume(float MusicVol, float SoundVol)
{
	if (MusicVol > 0)
	{
		MusicVolume = MusicVol;
		//ʹ�û�����������
		//AudioDevice->SetSoundMixClassOverride(SlAiSoundMix, SlAiMusicClass, MusicVolume, 1.f, 0.2f, false);
		//ѭ�����ñ�������
		for (TArray<USoundCue*>::TIterator It(MenuAudioResource.Find(FString("Music"))->CreateIterator()); It; ++It)
		{
			//��������
			(*It)->VolumeMultiplier = MusicVolume;
		}
	}
	if (SoundVol > 0)
	{
		SoundVolume = SoundVol;
		//ʹ�û�����������
		//AudioDevice->SetSoundMixClassOverride(SlAiSoundMix, SlAiMusicClass, MusicVolume, 1.f, 0.2f, false);
		for (TArray<USoundCue*>::TIterator It(MenuAudioResource.Find(FString("Sound"))->CreateIterator()); It; ++It)
		{
			//��������
			(*It)->VolumeMultiplier = SoundVolume;
		}
	}
	//���´浵����
	SlAiSingleton<SlAiJsonHandle>::Get()->UpdateRecordData(GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"), CurrentCulture), MusicVolume, SoundVolume, &RecordDataList);

}

/*
*  ANY_PACKAGE ����Ϸ�����ҵ���ӦName�µ�Enum
*/
template<typename TEnum>
FString SlAiDataHandle::GetEnumValueAsString(const FString& Name, TEnum Value)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
	if (!EnumPtr) {
		return FString("InValid");
	}
	return EnumPtr->GetNameStringByIndex((int32)Value);
}

template<typename TEnum>
TEnum SlAiDataHandle::GetEnumValueFromString(const FString& Name, FString Value)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
	if (!EnumPtr) {
		return TEnum(0);
	}
	return (TEnum)EnumPtr->GetIndexByName(FName(*FString(Value)));
}

void SlAiDataHandle::InitRecordData()
{
	RecordName = FString("");
	//��ȡ����
	FString Culture;
	//��ȡ�浵����
	SlAiSingleton<SlAiJsonHandle>::Get()->RecordDataJsonRead(Culture, MusicVolume, SoundVolume, RecordDataList);
	//��ʼ������
	ChangeLocalizationCulture(GetEnumValueFromString<ECultureTeam>(FString("ECultureTeam"), Culture));

	//�������
	SlAiHelper::Debug(Culture + FString("--") + FString::SanitizeFloat(MusicVolume) + FString("--") + FString::SanitizeFloat(SoundVolume), 20.f);
	//ѭ����ȡRecordDataList
	for (TArray<FString>::TIterator It(RecordDataList); It; ++It) {
		SlAiHelper::Debug(*It, 20.f);
	}
}

void SlAiDataHandle::InitializedMenuAudio()
{
	//��ȡ�༭����MenuStyle
	MenuStyle = &SlAiStyle::Get().GetWidgetStyle < FSlAiMenuStyle >("BPSlAiMenuStyle");

	//�����Դ�ļ�����Դ�б�
	TArray<USoundCue*> MusicList;
	MusicList.Add(Cast<USoundCue>(MenuStyle->MenuBackgroundMusic.GetResourceObject()));

	TArray<USoundCue*> SoundList;
	SoundList.Add(Cast<USoundCue>(MenuStyle->StartGameSound.GetResourceObject()));
	SoundList.Add(Cast<USoundCue>(MenuStyle->ExitGameSound.GetResourceObject()));
	SoundList.Add(Cast<USoundCue>(MenuStyle->MenuItemChangeSound.GetResourceObject()));

	//�����Դ��Map
	MenuAudioResource.Add(FString("Music"), MusicList);
	MenuAudioResource.Add(FString("Sound"), SoundList);

	//��������
	ResetMenuVolume(MusicVolume, SoundVolume);
}


