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

	//解析存档方法
	void RecordDataJsonRead(FString& Culture, float& MusicVolume, float& SoundVolume, TArray<FString>& RecordDataList);
	//修改存档
	void UpdateRecordData(FString Culture, float MusicVolume, float SoundVolume, TArray<FString>* RecordDataList);

	//解析物品属性
	void ObjectAttrJsonRead(TMap<int, TSharedPtr<ObjectAttribute>>& ObjectAttrMap);

private:
	//读取Json文件到字符串
	bool LoadStringFromFile(const FString& FileName, const FString& RelaPath, FString& ResultString);

	//FJsonObject转换为Json格式的字符串
	bool GetFStringInJsonData(const TSharedPtr<FJsonObject>& JsonObj, FString& JsonStr);

	//保存字符串到文件
	bool WriteFileWithJsonData(const FString& JsonStr, const FString& RelaPath, const FString& FileName);

	//定义一个从string转换到ObjectType的方法
	EObjectType::Type StringToObjectType(const FString ArgStr);
private:
	//存档文件名
	FString RecordDataFileName;

	//物品属性文件名
	FString ObjectAttrFileName;

	//资源属性文件名
	FString ResourceAttrFileName;

	//合成表文件名
	FString CompoundTableFileName;

	//相对路径
	FString RelativePath;
};

