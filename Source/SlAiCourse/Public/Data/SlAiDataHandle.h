// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlAiTypes.h"
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

public:
	//语言
	ECultureTeam CurrentCulture;

private:
	//创建单例
	static TSharedRef<SlAiDataHandle> Create();

private:
	static TSharedPtr<SlAiDataHandle> DataInstance;
};
