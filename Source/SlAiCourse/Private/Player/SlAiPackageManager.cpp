// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiPackageManager.h"
#include "SlAiHelper.h"

TSharedPtr<SlAiPackageManager> SlAiPackageManager::PackageInstance = NULL;

SlAiPackageManager::SlAiPackageManager()
{
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
		break;
	case EContainerType::Input:
		InputContainerList.Add(Container);
		break;
	case EContainerType::Normal:
		InputContainerList.Add(Container);
		break;
	case EContainerType::Shortcut:
		InputContainerList.Add(Container);
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
