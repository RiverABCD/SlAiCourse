// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiPackageManager.h"
#include "SlAiHelper.h"
#include "SlAiDataHandle.h"

TSharedPtr<SlAiPackageManager> SlAiPackageManager::PackageInstance = NULL;

SlAiPackageManager::SlAiPackageManager()
{
	//初始化物品和数量为0
	ObjectIndex = 0;
	ObjectNum = 0;
}

void SlAiPackageManager::Initialize()
{
	if (!PackageInstance.IsValid())
		PackageInstance = Create();
}

TSharedPtr<SlAiPackageManager> SlAiPackageManager::Get()
{
	Initialize();
	return PackageInstance;
}

TSharedRef<SlAiPackageManager> SlAiPackageManager::Create()
{
	TSharedRef<SlAiPackageManager> PackageRef = MakeShareable(new SlAiPackageManager());
	return PackageRef;
}


/*
TSharedPtr<SlAiPackageManager> SlAiPackageManager::Get()
{
	TSharedRef<SlAiPackageManager> PackageRef = MakeShareable(new SlAiPackageManager());

	if (!PackageInstance.IsValid())
		PackageInstance = PackageRef;//共享指针跟共享引用隐式转换了

	return PackageInstance;
}
*/

void SlAiPackageManager::InsertContainer(TSharedPtr<class SSlAiContainerBaseWidget> Container, EContainerType::Type InsertType)
{
	switch (InsertType)
	{
	case EContainerType::Output:
		OutputContainer = Container;
		OutputContainer->CompoundOutput.BindRaw(this, &SlAiPackageManager::CompoundOutput);
		OutputContainer->ThrowObject.BindRaw(this, &SlAiPackageManager::ThrowObject);
		break;
	case EContainerType::Input:
		Container->CompoundInput.BindRaw(this, &SlAiPackageManager::CompoundInput);
		InputContainerList.Add(Container);
		break;
	case EContainerType::Normal:
		NormalContainerList.Add(Container);
		break;
	case EContainerType::Shortcut:
		Container->PackShortChange.BindRaw(this, &SlAiPackageManager::PackShortChange);
		ShortcutContainerList.Add(Container);
		break;
	}
}

void SlAiPackageManager::UpdateHovered(FVector2D MousePos, FGeometry PackGeo)
{
	//先获取悬停的容器
	TSharedPtr<SSlAiContainerBaseWidget> CurrHoveredCon = LocateContainer(MousePos, PackGeo);
	//如果容器存在
	if (CurrHoveredCon.IsValid())
	{
		//设置当前容器悬停显示
		CurrHoveredCon->UpdateHovered(true);
		//如果上一容器存在，并且与当前容器不相同
		if (LastHoveredCon.IsValid() && LastHoveredCon.Get() != CurrHoveredCon.Get())
		{
			//更新悬停显示
			LastHoveredCon->UpdateHovered(false);
		}
	}
	else
	{
		//当前容器不存在且上一容器存在，取消上一容器的悬停显示
		if (LastHoveredCon.IsValid())
		{
			LastHoveredCon->UpdateHovered(false);
		}
	}
	
	//更新上一悬停容器
	LastHoveredCon = CurrHoveredCon;
}

TSharedPtr<SSlAiContainerBaseWidget> SlAiPackageManager::LocateContainer(FVector2D MousePos, FGeometry PackGeo)
{
	//迭代找到指向的容器
	for (TArray<TSharedPtr<SSlAiContainerBaseWidget>>::TIterator It(ShortcutContainerList); It; ++It) {
		//获取区域
		FVector2D StartPos = PackGeo.AbsoluteToLocal((*It)->GetCachedGeometry().AbsolutePosition);

		FVector2D EndPos = StartPos + FVector2D(80.f, 80.f);

		//判断鼠标位置是否在区域内,在的话直接返回这个容器
		if (MousePos.X >= StartPos.X && MousePos.X <= EndPos.X && MousePos.Y >= StartPos.Y && MousePos.Y <= EndPos.Y)
		{
			return *It;
		}
	}
	for (TArray<TSharedPtr<SSlAiContainerBaseWidget>>::TIterator It(NormalContainerList); It; ++It) {
		//获取区域
		FVector2D StartPos = PackGeo.AbsoluteToLocal((*It)->GetCachedGeometry().AbsolutePosition);
		FVector2D EndPos = StartPos + FVector2D(80.f, 80.f);
		//判断鼠标位置是否在区域内,在的话直接返回这个容器
		if (MousePos.X >= StartPos.X && MousePos.X <= EndPos.X && MousePos.Y >= StartPos.Y && MousePos.Y <= EndPos.Y) {
			return *It;
		}
	}
	for (TArray<TSharedPtr<SSlAiContainerBaseWidget>>::TIterator It(InputContainerList); It; ++It) {
		//获取区域
		FVector2D StartPos = PackGeo.AbsoluteToLocal((*It)->GetCachedGeometry().AbsolutePosition);
		FVector2D EndPos = StartPos + FVector2D(80.f, 80.f);
		//判断鼠标位置是否在区域内,在的话直接返回这个容器
		if (MousePos.X >= StartPos.X && MousePos.X <= EndPos.X && MousePos.Y >= StartPos.Y && MousePos.Y <= EndPos.Y) {
			return *It;
		}
	}
	//这里处理输出容器的
	//获取区域
	FVector2D StartPos = PackGeo.AbsoluteToLocal(OutputContainer->GetCachedGeometry().AbsolutePosition);
	FVector2D EndPos = StartPos + FVector2D(80.f, 80.f);
	//判断鼠标位置是否在区域内,在的话直接返回这个容器
	if (MousePos.X >= StartPos.X && MousePos.X <= EndPos.X && MousePos.Y >= StartPos.Y && MousePos.Y <= EndPos.Y) {
		return OutputContainer;
	}
	//最后返回空
	return nullptr;
}

void SlAiPackageManager::LeftOption(FVector2D MousePos, FGeometry PackGeo)
{
	//先获取点击的容器
	TSharedPtr<SSlAiContainerBaseWidget> ClickedContainer = LocateContainer(MousePos, PackGeo);
	//如果容器存在,执行容器事件
	if (ClickedContainer.IsValid())
	{
		ClickedContainer->LeftOperate(ObjectIndex, ObjectNum, ObjectIndex, ObjectNum);
	}
	//如果容器不存在并且手上物品不为空
	if (!ClickedContainer.IsValid() && ObjectIndex != 0)
	{
		//把物品丢弃,待填写
		ThrowObject(ObjectIndex, ObjectNum);
		//重置物品
		ObjectIndex = ObjectNum = 0;
	}
}

void SlAiPackageManager::RightOption(FVector2D MousePos, FGeometry PackGeo)
{
	//先获取点击的容器
	TSharedPtr<SSlAiContainerBaseWidget> ClickedContainer = LocateContainer(MousePos, PackGeo);
	//如果容器存在,执行容器事件
	if (ClickedContainer.IsValid()) {
		ClickedContainer->RightOperate(ObjectIndex, ObjectNum, ObjectIndex, ObjectNum);
	}
}

void SlAiPackageManager::ThrowObject(int ObjectID, int Num)
{
	PlayerThrowObject.ExecuteIfBound(ObjectID, Num);
}

void SlAiPackageManager::PackShortChange(int ShortcutID, int ObjectID, int ObjectNumber)
{
	//执行委托,绑定的方法是PlayerState的ChangeHandObject,在playercharacter下进行绑定
	ChangeHandObject.ExecuteIfBound(ShortcutID, ObjectID, ObjectNumber);
}

bool SlAiPackageManager::Multiplyable(int ObjectID)
{
	//获取物品属性
	TSharedPtr<ObjectAttribute> ObjectAttr = *SlAiDataHandle::Get()->ObjectAttrMap.Find(ObjectID);
	//返回是否是武器或者工具
	return (ObjectAttr->ObjectType != EObjectType::Tool&&ObjectAttr->ObjectType != EObjectType::Weapon);
}

void SlAiPackageManager::CompoundOutput(int ObjectID, int Num)
{
	//如果生产为0,直接return
	if (ObjectID == 0) return;
	//合成表结构数组
	TArray<int> TableMap;
	for (TArray<TSharedPtr<SSlAiContainerBaseWidget>>::TIterator It(InputContainerList); It; ++It) {
		TableMap.Add((*It)->GetIndex());
	}
	TableMap.Add(ObjectID);
	//消耗数量的数组
	TArray<int> ExpendMap;
	//遍历找出符合的合成表并且拿到消耗数量的数组
	for (TArray<TSharedPtr<CompoundTable>>::TIterator It(SlAiDataHandle::Get()->CompoundTableMap); It; ++It) {
		//如果找到符合的直接跳出循环
		if ((*It)->DetectExpend(&TableMap, Num, ExpendMap)) break;
	}
	//如果消耗数组元素数量不是9,直接return
	if (ExpendMap.Num() != 9) return;
	//循环设置合成输入表的属性
	for (int i = 0; i < 9; ++i) {
		//如果原有数量减去消耗数量已经小于等于0,直接把物品ID设置为0
		int InputID = (InputContainerList[i]->GetNum() - ExpendMap[i] <= 0) ? 0 : InputContainerList[i]->GetIndex();
		int InputNum = (InputID == 0) ? 0 : (InputContainerList[i]->GetNum() - ExpendMap[i]);
		//重置参数
		InputContainerList[i]->ResetContainerPara(InputID, InputNum);
	}
}

void SlAiPackageManager::CompoundInput()
{
	//获取合成台9个容器的物品id和数量写进两个数组
	TArray<int> IDMap;
	TArray<int> NumMap;
	for (TArray<TSharedPtr<SSlAiContainerBaseWidget>>::TIterator It(InputContainerList); It; ++It) {
		IDMap.Add((*It)->GetIndex());
		NumMap.Add((*It)->GetNum());
	}
	//定义检测出来输出框的ID和数量
	int OutputIndex = 0;
	int OutputNum = 0;
	//迭代合成表进行检测
	for (TArray<TSharedPtr<CompoundTable>>::TIterator It(SlAiDataHandle::Get()->CompoundTableMap); It; ++It) {
		(*It)->DetectTable(&IDMap, &NumMap, OutputIndex, OutputNum);
		//如果检测出来了,直接跳出循环
		if (OutputIndex != 0 && OutputNum != 0) break;
	}
	//下面对OutputContainer进行赋值
	//先判断是否可以叠加
	if (Multiplyable(OutputIndex)) {
		//可以叠加的话就直接赋值,包括0,0
		OutputContainer->ResetContainerPara(OutputIndex, OutputNum);
	}
	else {
		//不可以叠加的话只添加一个
		OutputContainer->ResetContainerPara(OutputIndex, 1);
	}
}

bool SlAiPackageManager::SearchFreeSpace(int ObjectID, TSharedPtr<SSlAiContainerBaseWidget>& FreeContainer)
{
	//空容器引用
	TSharedPtr<SSlAiContainerBaseWidget> EmptyContainer;

	for (TArray<TSharedPtr<SSlAiContainerBaseWidget>>::TIterator It(ShortcutContainerList); It; ++It) {
		//如果优先容器有没有引用
		if (!FreeContainer.IsValid())
		{
			//如果这个容器的物品和输入物品ID相同并且有空间,直接指定
			if ((*It)->RemainSpace(ObjectID))
			{
				FreeContainer = *It;
				return true;
			}
		}
		//如果空容器无引用
		if (!EmptyContainer.IsValid()) 
		{
			if ((*It)->IsEmpty()) EmptyContainer = *It;
		}
	}

	for (TArray<TSharedPtr<SSlAiContainerBaseWidget>>::TIterator It(NormalContainerList); It; ++It) {
		//如果空容器无引用
		if (!EmptyContainer.IsValid()) {
			if ((*It)->IsEmpty()) EmptyContainer = *It;
		}
		//如果优先容器有没有引用
		if (!FreeContainer.IsValid())
		{
			//如果这个容器的物品和输入物品ID相同并且有空间,直接指定
			if ((*It)->RemainSpace(ObjectID))
			{
				FreeContainer = *It;
				return true;
			}
		}
	}
	//如运行到这里说明需要指定空容器
	if (EmptyContainer.IsValid()) {
		FreeContainer = EmptyContainer;
		return true;
	}
	//如果连空容器都没有,返回false
	return false;
}

bool SlAiPackageManager::SearchFreeSpace(int ObjectID)
{
	TSharedPtr<SSlAiContainerBaseWidget> FreeContainer;
	return SearchFreeSpace(ObjectID, FreeContainer);
}

void SlAiPackageManager::AddObject(int ObjectID)
{
	TSharedPtr<SSlAiContainerBaseWidget> FreeContainer;
	if (SearchFreeSpace(ObjectID, FreeContainer)) {
		//添加物品到容器
		FreeContainer->AddObject(ObjectID);
	}
}

bool SlAiPackageManager::EatUpEvent(int ShortcutID)
{
	//获取物品属性
	TSharedPtr<ObjectAttribute> ObjectAttr = *SlAiDataHandle::Get()->ObjectAttrMap.Find(ShortcutContainerList[ShortcutID]->GetIndex());
	//如果这个物品是食物
	if (ObjectAttr->ObjectType == EObjectType::Food)
	{
		//新的物品数量
		int NewNum = (ShortcutContainerList[ShortcutID]->GetNum() - 1) < 0 ? 0 : (ShortcutContainerList[ShortcutID]->GetNum() - 1);
		//新的物品ID
		int NewIndex = NewNum == 0 ? 0 : ShortcutContainerList[ShortcutID]->GetIndex();
		//更新这个容器属性
		ShortcutContainerList[ShortcutID]->ResetContainerPara(NewIndex, NewNum);
		//返回成功吃掉食物
		return true;
	}
	return false;
}
