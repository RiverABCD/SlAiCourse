// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSlAiContainerBaseWidget.h"
#include "SlAiTypes.h"

/**
 * 
 */
class SLAICOURSE_API SlAiPackageManager
{
public:
	SlAiPackageManager();

	static void Initialize();

	static TSharedPtr<SlAiPackageManager> Get();

	//添加容器
	void InsertContainer(TSharedPtr<class SSlAiContainerBaseWidget> Container, EContainerType::Type InsertType);

	//更新悬停的容器颜色
	void UpdateHovered(FVector2D MousePos, FGeometry PackGeo);

	//左键事件,参数是鼠标位置和PackageWidget的Geometry
	void LeftOption(FVector2D MousePos, FGeometry PackGeo);

	//右键事件,参数是鼠标位置和PackageWidget的Geometry
	void RightOption(FVector2D MousePos, FGeometry PackGeo);

	//是否有插入物品的空间,提供给外部访问
	bool SearchFreeSpace(int ObjectID);

	//添加物品到背包
	void AddObject(int ObjectID);
	//吃东西,传入快捷栏的ID,传回是否成功吃掉
	bool EatUpEvent(int ShortcutID);

	//加载存档
	void LoadRecord(TArray<int32>* InputIndex, TArray<int32>* InputNum, TArray<int32>* NormalIndex, TArray<int32>* NormalNum, TArray<int32>* ShortcutIndex, TArray<int32>* ShortcutNum);

	void SaveData(TArray<int32>& InputIndex, TArray<int32>& InputNum, TArray<int32>& NormalIndex, TArray<int32>& NormalNum, TArray<int32>& ShortcutIndex, TArray<int32>& ShortcutNum);


public:
	//鼠标物品ID
	int ObjectIndex;
	//鼠标物品数量
	int ObjectNum;

	//丢弃物品委托,绑定的方法是PlayerState的PlayerThrowObject
	FThrowObject PlayerThrowObject;
	//修改快捷栏信息委托
	FPackShortChange ChangeHandObject;

private:
	//创建实例方法
	static TSharedRef<SlAiPackageManager> Create();

	//获取鼠标指向的容器
	TSharedPtr<SSlAiContainerBaseWidget> LocateContainer(FVector2D MousePos, FGeometry PackGeo);

	//委托所绑定的函数
	//丢弃物品事件
	void ThrowObject(int ObjectID, int Num);
	//合成提取事件
	void CompoundOutput(int ObjectID, int Num);
	//合成输入事件
	void CompoundInput();
	//快捷栏变换事件
	void PackShortChange(int ShortcutID, int ObjectID, int ObjectNum);
	//获取是否可以叠加
	bool Multiplyable(int ObjectID);
	//是否有插入物品的空间,每次只会插入一个,返回可以插入的那个容器
	bool SearchFreeSpace(int ObjectID, TSharedPtr<SSlAiContainerBaseWidget>& FreeContainer);

private:
	//单例私有指针
	static TSharedPtr<SlAiPackageManager> PackageInstance;

	//容器列表
	TArray<TSharedPtr<SSlAiContainerBaseWidget>> InputContainerList;
	TArray<TSharedPtr<SSlAiContainerBaseWidget>> NormalContainerList;
	TArray<TSharedPtr<SSlAiContainerBaseWidget>> ShortcutContainerList;
	//输出容器只有一个
	TSharedPtr<SSlAiContainerBaseWidget> OutputContainer;

	//上一个悬停的容器
	TSharedPtr<SSlAiContainerBaseWidget> LastHoveredCon;
};
