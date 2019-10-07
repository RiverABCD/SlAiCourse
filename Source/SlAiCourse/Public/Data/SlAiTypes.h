// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBorder.h"
#include "SImage.h"
#include "STextBlock.h"
#include "SlateBasics.h"

/**
 * 
 */

UENUM()
enum class ECultureTeam : uint8 {
	EN = 0,
	ZH
};

//Menu��ť������
namespace EMenuItem {
	enum Type {
		None,
		StartGame,
		GameOption,
		QuitGame,
		NewGame,
		LoadRecord,
		StartGameGoBack,
		GameOptionGoBack,
		NewGameGoBack,
		ChooseRecordGoBack,
		EnterGame,
		EnterRecord
	};
}

//Menu��������
namespace EMenuType
{
	enum Type	
	{
		None,
		MainMenu,
		StartGame,
		GameOption,
		NewGame,
		ChooseRecord
	};
}

//Menu����״̬ö��
namespace EMenuAnim
{
	enum Type
	{
		Stop, //ֹͣ����
		Close, //�ر�Menu
		Open  //��Menu
	};
}

//�ӽ�ģʽ
namespace EGameViewMode {
	enum Type
	{
		First,
		Third
	};
}

//�ϰ�������״̬
namespace EUpperBody
{
	enum Type
	{
		None,
		Punch,
		Hit,
		Fight,
		PickUp,
		Eat
	};
}

//��Ʒ����
namespace EObjectType
{
	enum Type
	{
		Normal = 0,//��ͨ��Ʒ,ľͷ,ʯͷ
		Food,//ʳ��,ƻ��,��
		Tool,//����,����,����
		Weapon//����,��
	};
}

//��Ʒ���Խṹ��
struct ObjectAttribute
{
	FText EN;//Ӣ����
	FText ZH;//������
	EObjectType::Type ObjectType;//��Ʒ����
	int PlantAttack;//��ֲ��Ĺ�����
	int MetalAttcck;//�Խ�����Դ�Ĺ�����
	int AnimalAttack;//�Զ���Ĺ�����
	int AffectRange;//��������
	FString TexPath;//ͼƬ·��
	//���캯��
	ObjectAttribute(const FText ENName, const FText ZHName, const EObjectType::Type OT, const int PA, const int MA, const int AA, const int AR, const FString TP)
	{
		EN = ENName;
		ZH = ZHName;
		ObjectType = OT;
		PlantAttack = PA;
		MetalAttcck = MA;
		AnimalAttack = AA;
		AffectRange = AR;
		TexPath = TP;
	}
#if 0
	FString ToString() {
		return EN.ToString() + FString("--") + ZH.ToString() + FString("--") + FString::FromInt((int)ObjectType) + FString("--") \
			+ FString::FromInt(PlantAttack) + FString("--") + FString::FromInt(MetalAttcck) + FString("--")\
			+ FString::FromInt(AnimalAttack) + FString("--") + FString::FromInt(AffectRange) + FString("--") + TexPath;

	}
#endif
};

//����������ṹ��
struct ShortcutContainer
{
	//��ƷID
	int ObjectIndex;
	int ObjectNum;
	TSharedPtr<SBorder> ContainerBorder;
	TSharedPtr<SBorder> ObjectImage;
	TSharedPtr<STextBlock> ObjectNumText;
	const FSlateBrush* NormalContainerBrush;
	const FSlateBrush* ChoosedContainerBrush;
	TArray<const FSlateBrush*>* ObjectBrushList;

	ShortcutContainer(TSharedPtr<SBorder> CB, TSharedPtr<SBorder> OI, TSharedPtr<STextBlock> ONT, const FSlateBrush* NCB, const FSlateBrush* CCB, TArray<const FSlateBrush*>* OBL)
	{
		ContainerBorder = CB;
		ObjectImage = OI;
		ObjectNumText = ONT;
		NormalContainerBrush = NCB;
		ChoosedContainerBrush = CCB;
		ObjectBrushList = OBL;

		//��ʼ����ʾ����
		ObjectIndex = 0;
		ObjectNum = 0;
		ContainerBorder->SetBorderImage(NormalContainerBrush);
		ObjectImage->SetBorderImage((*ObjectBrushList)[0]);
	}

	//�����Ƿ�ѡ�е�ǰ����Ʒ��true����Ҫѡ�У�������Ʒ����
	int SetChoosed(bool Option)
	{
		if (Option)
		{
			ContainerBorder->SetBorderImage(ChoosedContainerBrush);
		} 
		else
		{
			ContainerBorder->SetBorderImage(NormalContainerBrush);
		}
		return ObjectIndex;
	}

	//����Index
	ShortcutContainer* SetObject(int NewIndex)
	{
		ObjectIndex = NewIndex;
		ObjectImage->SetBorderImage((*ObjectBrushList)[ObjectIndex]);
		return this;
	}

	//��������
	ShortcutContainer* SetObjectNum(int Num = 0)
	{
		ObjectNum = Num;
		//�������Ϊ0����1������ʵ����
		if (ObjectNum == 0 || ObjectNum == 1)
		{
			ObjectNumText->SetText(FString(""));
		} 
		else
		{
			ObjectNumText->SetText(FString::FromInt(ObjectNum));
		}
		return this;
	}
};

//��Դ����
namespace EResourceType {
	enum Type {
		Plant=0,
		Metal,
		Animal

	};
}
//��Դ���Խṹ
struct ResourceAttribute
{
	FText EN;//Ӣ����
	FText ZH;//������
	EResourceType::Type ResourceType;
	int HP;
	TArray<TArray<int>> FlobObjectInfo;

	ResourceAttribute(const FText ENName, const FText ZHName, const EResourceType::Type RT, const int HPValue, TArray<TArray<int>>* FOI) {
		EN = ENName;
		ZH = ZHName;
		ResourceType = RT;
		HP = HPValue;

		//������Ԫ�ص�������������FlobObjectInfo(json see path"\Content\Res\ConfigData\ResourceAttribute.json")
		for (TArray<TArray<int>>::TIterator It(*FOI); It; ++It) {
			TArray<int> FlobObjectInfoItem;
			for (TArray<int>::TIterator Ih(*It); Ih; ++Ih) {
				FlobObjectInfoItem.Add(*Ih);
			}
			FlobObjectInfo.Add(FlobObjectInfoItem);
		}
	}

	//debug the json data ��ʱ����
	FString ToString() {
		FString InfoStr;
		for (TArray<TArray<int>>::TIterator It(FlobObjectInfo); It; ++It) {
			for (TArray<int>::TIterator Ih(*It); Ih; ++Ih)
			{
				InfoStr += FString::FromInt(*Ih) + FString(". ");
			}
			InfoStr += FString("__");
		}
		return EN.ToString() + FString("--") + ZH.ToString() + FString("--") \
			+ FString::FromInt((int)ResourceType) + FString("--")\
			+ FString::FromInt(HP) + FString("--") + InfoStr;
	}
};

//Game�������
namespace EGameUIType
{
	enum Type
	{
		Game,//��ϷģʽUI
		Pause,//��ͣ
		Lose,//���ˣ�����
		Package,//����
		ChatRoom//������
	};
}

//������������
namespace EContainerType
{
	enum Type
	{
		Output,//�ϳɱ����
		Input,//�ϳɱ�����
		Normal,//��ͨ����
		Shortcut,//���������
	};
}

//�ϳɱ�ṹ��
struct CompoundTable
{
	//�ϳ�ͼ
	TArray<int> CompoundMap;
	//���캯��
	CompoundTable(TArray<int> *InsertMap) {
		for (TArray<int>::TIterator It(*InsertMap); It; ++It) {
			CompoundMap.Add(*It);
		}
	}

	//�����ϱ�������ƷID������
	void DetectTable(TArray<int>* IDMap, TArray<int>* NumMap, int& OutputID, int& OutputNum)
	{
		//��Ĭ���趨���IDΪ�����ID
		int TempID = CompoundMap[9];
		//���趨�������Ϊ64,һ��һ���ȥ
		int TempNum = 64;
		for (int i = 0; i < 9; ++i)
		{
			if ((*IDMap)[i] == CompoundMap[i])
			{
				if ((*IDMap)[i] != 0) TempNum = (*NumMap)[i] < TempNum ? (*NumMap)[i] : TempNum;
			}
			else
			{
				TempID = TempNum = 0;
				break;
			}
		}
		//������ID��Ϊ��,����Output����
		if (TempID != 0 && TempNum != 0) {
			OutputID = TempID;
			OutputNum = TempNum;
		}
	}

	//��������ĵ���ƷID�����ID�����Լ�����������ѯ���Ƿ�ƥ������ϳɱ��������������
	bool DetectExpend(TArray<int>* TableMap, int ProductNum, TArray<int>& ExpendMap)
	{
		//�Ƿ�ƥ������ϳɱ�,��ʼ����Ϊtrue
		bool IsMatch = true;
		for (int i = 0; i < 10; ++i) {
			//ֻҪ��һ��������,ֱ������false
			if ((*TableMap)[i] != CompoundMap[i])
			{
				IsMatch = false;
				break;
			}
		}
		//���ƥ��
		if (IsMatch) {
			for (int i = 0; i < 9; ++i) {
				//�����Ϊ0,ֱ��Add����������
				if (CompoundMap[i] != 0) {
					ExpendMap.Add(ProductNum);
				}
				else {
					ExpendMap.Add(0);
				}
			}
		}
		//�����Ƿ�ƥ��
		return IsMatch;
	}

	//��ӡ�ַ���
	FString ToString() 
	{
		FString OutputString("");
		for (TArray<int>::TIterator It(CompoundMap); It; ++It) 
		{
			OutputString += FString::FromInt(*It) + FString("__");
		}
		return OutputString;
	}
};

//����AI״̬
UENUM(BlueprintType)
enum  class EEnemyAIState : uint8
{
	ES_Patrol    UMETA(DisplayName = "Patrol"),
	ES_Chase     UMETA(DisplayName = "Chase"),
	ES_Escape    UMETA(DisplayName = "Escape"),
	ES_Attack    UMETA(DisplayName = "Attack"),
	ES_Hurt      UMETA(DisplayName = "Hurt"),
	ES_Defence   UMETA(DisplayName = "Defence"),
	ES_Dead      UMETA(DisplayName = "Dead")
};




//���˹���״̬
UENUM(BlueprintType)
enum class EEnemyAttackType : uint8
{
	EA_Normal   UMETA(DisplayName = "Normal"),
	EA_Dash     UMETA(DisplayName = "Dash"),
	EA_Pursuit  UMETA(DisplayName = "Pursuit")
};


//С��ͼ����״̬
namespace EMiniMapSizeMode
{
	enum Type
	{
		None,
		Add,
		Reduce
	};
}