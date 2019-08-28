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
	//修改中英文
	void ChangeLocalizationCulture(ECultureTeam Culture);
	//修改菜单音量
	void ResetMenuVolume(float MusicVol, float SoundVol);
	//游戏数据初始化
	void InitializeGameData();

public:
	//语言
	ECultureTeam CurrentCulture;
	//音量
	float MusicVolume;
	float SoundVolume;
	//存档数据
	TArray<FString> RecordDataList;
	//存档名
	FString RecordName;
	//物品属性图
	TMap<int, TSharedPtr<ObjectAttribute>> ObjectAttrMap;
	//物品贴图资源数组
	TArray<const FSlateBrush*> ObjectBrushList;
private:
	//创建单例
	static TSharedRef<SlAiDataHandle> Create();
	//根据Enum类型获取字符串
	template <typename TEnum>
	FString GetEnumValueAsString(const FString& name,TEnum Value);
	//根据字符串获取Enum值
	template <typename TEnum>
	TEnum GetEnumValueFromString(const FString& name, FString Value);

	//初始化存档数据
	void InitRecordData();
	//初始化Menu声音数据
	void InitializedMenuAudio();
	//初始化物品属性图
	void InitObjectAttr();
	//初始化资源属性图
	//void InitResourceAttrMap();
	//初始化合成表图
	//void InitCompoundTableMap();
	//初始化Game声音数据
	//void InitializeGameAudio();

private:
	static TSharedPtr<SlAiDataHandle> DataInstance;
	//保存Menu的声音
	TMap<FString, TArray<USoundCue*>> MenuAudioResource;
	//获取MenuStyle,里面存放有声音文件
	const struct FSlAiMenuStyle* MenuStyle;
	//获取GameStyle
	const struct FSlAiGameStyle* GameStyle;
	//音乐组件
	class USoundMix* SlAiSoundMix;
	class USoundClass* SlAiMusicClass;
	USoundClass* SlAiSoundClass;
	class FAudioDevice* AudioDevice;

};


