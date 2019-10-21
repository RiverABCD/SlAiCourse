// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiDataHandle.h"
#include "Internationalization.h"
#include "SlAiSingleton.h"
#include "SlAiJsonHandle.h"
#include "SlAiHelper.h"
#include "SlAiStyle.h"
#include "SlAiMenuWidgetStyle.h"
#include "SlAiGameWidgetStyle.h"
#include "Sound/SoundCue.h"

#include "AudioDevice.h"
#include "Sound/SoundMix.h"
#include "Sound/SoundClass.h"

TSharedPtr<SlAiDataHandle> SlAiDataHandle::DataInstance = NULL;

SlAiDataHandle::SlAiDataHandle()
{
	//初始化存档
	InitRecordData();
	//初始化音乐数据
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
	//赋值
	CurrentCulture = Culture;
	//更新存档数据
	SlAiSingleton<SlAiJsonHandle>::Get()->UpdateRecordData(GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"), CurrentCulture), MusicVolume, SoundVolume, &RecordDataList);
}

void SlAiDataHandle::ResetMenuVolume(float MusicVol, float SoundVol)
{
	if (MusicVol > 0)
	{
		MusicVolume = MusicVol;
		//使用混音器来设置
		//AudioDevice->SetSoundMixClassOverride(SlAiSoundMix, SlAiMusicClass, MusicVolume, 1.f, 0.2f, false);
		//循环设置背景音量
		for (TArray<USoundCue*>::TIterator It(MenuAudioResource.Find(FString("Music"))->CreateIterator()); It; ++It)
		{
			//设置音量
			(*It)->VolumeMultiplier = MusicVolume;
		}
	}
	if (SoundVol > 0)
	{
		SoundVolume = SoundVol;
		//使用混音器来设置
		//AudioDevice->SetSoundMixClassOverride(SlAiSoundMix, SlAiMusicClass, MusicVolume, 1.f, 0.2f, false);
		for (TArray<USoundCue*>::TIterator It(MenuAudioResource.Find(FString("Sound"))->CreateIterator()); It; ++It)
		{
			//设置音量
			(*It)->VolumeMultiplier = SoundVolume;
		}
	}
	//更新存档数据
	SlAiSingleton<SlAiJsonHandle>::Get()->UpdateRecordData(GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"), CurrentCulture), MusicVolume, SoundVolume, &RecordDataList);

}

void SlAiDataHandle::ResetGameVolume(float MusicVol, float SoundVol)
{
	if (MusicVol > 0)
	{
		MusicVolume = MusicVol;
		//使用混音器来设置
		AudioDevice->SetSoundMixClassOverride(SlAiSoundMix, SlAiMusicClass, MusicVolume, 1.f, 0.2f, false);
	}
	if (SoundVol > 0)
	{
		SoundVolume = SoundVol;
		//使用混音器来设置
		AudioDevice->SetSoundMixClassOverride(SlAiSoundMix, SlAiSoundClass, SoundVolume, 1.f, 0.2f, false);
	}
	//更新存档数据
	SlAiSingleton<SlAiJsonHandle>::Get()->UpdateRecordData(GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"), CurrentCulture), MusicVolume, SoundVolume, &RecordDataList);
}

/*
*  ANY_PACKAGE 从游戏包中找到对应Name下的Enum
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
	//获取语言
	FString Culture;
	//读取存档数据
	SlAiSingleton<SlAiJsonHandle>::Get()->RecordDataJsonRead(Culture, MusicVolume, SoundVolume, RecordDataList);
	//初始化语言
	ChangeLocalizationCulture(GetEnumValueFromString<ECultureTeam>(FString("ECultureTeam"), Culture));

	//输出调试
	SlAiHelper::Debug(Culture + FString("--") + FString::SanitizeFloat(MusicVolume) + FString("--") + FString::SanitizeFloat(SoundVolume), 20.f);
	//循环读取RecordDataList
	for (TArray<FString>::TIterator It(RecordDataList); It; ++It) {
		SlAiHelper::Debug(*It, 20.f);
	}
}

void SlAiDataHandle::InitializedMenuAudio()
{
	//获取编辑器的MenuStyle
	MenuStyle = &SlAiStyle::Get().GetWidgetStyle < FSlAiMenuStyle >("BPSlAiMenuStyle");

	//添加资源文件到资源列表
	TArray<USoundCue*> MusicList;
	MusicList.Add(Cast<USoundCue>(MenuStyle->MenuBackgroundMusic.GetResourceObject()));

	TArray<USoundCue*> SoundList;
	SoundList.Add(Cast<USoundCue>(MenuStyle->StartGameSound.GetResourceObject()));
	SoundList.Add(Cast<USoundCue>(MenuStyle->ExitGameSound.GetResourceObject()));
	SoundList.Add(Cast<USoundCue>(MenuStyle->MenuItemChangeSound.GetResourceObject()));

	//添加资源到Map
	MenuAudioResource.Add(FString("Music"), MusicList);
	MenuAudioResource.Add(FString("Sound"), SoundList);

	//重置声音
	ResetMenuVolume(MusicVolume, SoundVolume);
}

void SlAiDataHandle::InitializeGameData()
{
	//初始化物品属性图
	InitObjectAttr();
	//初始化资源属性图
	InitResourceAttrMap();
	//初始化合成表图
	InitCompoundTableMap();
	//初始化声音设置
	InitializeGameAudio();
}

void SlAiDataHandle::AddNewRecord()
{
	//将现在的存档名添加到数组
	RecordDataList.Add(RecordName);
	//更新json数据
	SlAiSingleton<SlAiJsonHandle>::Get()->UpdateRecordData(GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"), CurrentCulture), MusicVolume, SoundVolume, &RecordDataList);
}

void SlAiDataHandle::InitObjectAttr()
{
	SlAiSingleton<SlAiJsonHandle>::Get()->ObjectAttrJsonRead(ObjectAttrMap);
	//获取GameStyle
	GameStyle = &SlAiStyle::Get().GetWidgetStyle<FSlAiGameStyle>("BPSlAiGameStyle");
	//填充笔刷数组
	ObjectBrushList.Add(&GameStyle->EmptyBrush);
	ObjectBrushList.Add(&GameStyle->ObjectBrush_1);
	ObjectBrushList.Add(&GameStyle->ObjectBrush_2);
	ObjectBrushList.Add(&GameStyle->ObjectBrush_3);
	ObjectBrushList.Add(&GameStyle->ObjectBrush_4);
	ObjectBrushList.Add(&GameStyle->ObjectBrush_5);
	ObjectBrushList.Add(&GameStyle->ObjectBrush_6);
	ObjectBrushList.Add(&GameStyle->ObjectBrush_7);

	////动态生成Object的图片Brush,这段代码会引起奔溃
	//for (int i = 1; i < ObjectAttrMap.Num(); ++i) {
	//	//测试函数,动态创建FSlateBrush,一定要创建指针,否则会在函数结束时销毁资源
	//	FSlateBrush* ObjectBrush = new FSlateBrush();
	//	ObjectBrush->ImageSize = FVector2D(80.f, 80.f);
	//	ObjectBrush->DrawAs = ESlateBrushDrawType::Image;
	//	UTexture2D* ObjectTex = LoadObject<UTexture2D>(NULL, *(*ObjectAttrMap.Find(i))->TexPath);
	//	ObjectBrush->SetResourceObject(ObjectTex);
	//	ObjectBrushList.Add(ObjectBrush);
	//}

}

void SlAiDataHandle::InitResourceAttrMap()
{
	SlAiSingleton<SlAiJsonHandle>::Get()->ResourceAttrJsonRead(ResourceAttrMap);
#if 0
	for (TMap<int, TSharedPtr<ResourceAttribute>>::TIterator It(ResourceAttrMap); It; ++It)
	{
		SlAiHelper::Debug((It->Value)->ToString(), 120.f);
	}
#endif
}

void SlAiDataHandle::InitCompoundTableMap()
{
	SlAiSingleton<SlAiJsonHandle>::Get()->CompoundTableJsonRead(CompoundTableMap);
}

void SlAiDataHandle::InitializeGameAudio()
{
	//获取混音器和音类
	SlAiSoundMix = LoadObject<USoundMix>(NULL, TEXT("SoundMix'/Game/Blueprint/Sound/SlAiSoundMix.SlAiSoundMix'"));
	SlAiMusicClass = LoadObject<USoundClass>(NULL, TEXT("SoundClass'/Game/Blueprint/Sound/SlAiMusicClass.SlAiMusicClass'"));
	SlAiSoundClass = LoadObject<USoundClass>(NULL, TEXT("SoundClass'/Game/Blueprint/Sound/SlAiSoundClass.SlAiSoundClass'"));

	//获取声音设备
	AudioDevice = GEngine->GetMainAudioDevice();
	//推送混音器到设备
	AudioDevice->PushSoundMixModifier(SlAiSoundMix);
	//根据音量设置一次声音

}
