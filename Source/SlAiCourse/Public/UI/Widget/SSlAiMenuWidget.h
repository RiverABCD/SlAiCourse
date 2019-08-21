// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlAiTypes.h"
#include "Widgets/SCompoundWidget.h"
#include "SSlAiGameOptionWidget.h"
#include "SSlAiNewGameWidget.h"
#include "SSlAiChooseRecordWidget.h"

class SBox;
class STextBlock;
class SVerticalBox;
struct MenuGroup;
class SSlAiGameOptionWidget;
class SSlAiNewGameWidget;
class SSlAiChooseRecordWidget;
/**
 * 
 */
class SLAICOURSE_API SSlAiMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiMenuWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	//��дtick����
	virtual void Tick(const FGeometry& AllottedGeometry,const double InCurrentTime,const float InDeltaTime) override;

private:
	//�󶨵�����MenuItem�ķ���
	void MenuItemOnClicked(EMenuItem::Type ItemType);
	//�޸�����
	void ChangeCulture(ECultureTeam Culture);
	//�޸�����
	void ChangeVolume(const float MusicVolume, const float SoundVolume);
	//��ʼ�����пؼ�
	void InitializedMenuList();
	//ѡ����ʾ�Ľ���
	void ChooseWidget(EMenuType::Type WidgetType);
	//�޸Ĳ˵��Ĵ�С
	void ResetWidgetSize(float NewWidget, float NewHeight);
	//��ʼ���������
	void InitializedAnimation();
	//���Źرն���
	void PlayClose(EMenuType::Type NewMenu);
	//�˳���Ϸ
	void QuitGame();
	//������Ϸ
	void EnterGame();

private:
	//������ڵ�
	TSharedPtr<SBox> RootSizeBox;
	//��ȡMenuStyle
	const struct FSlAiMenuStyle* MenuStyle;
	//�������
	TSharedPtr<STextBlock> TitleText;
	//�������洹ֱ�б�
	TSharedPtr<SVerticalBox> ContentBox;
	//����˵���
	TMap<EMenuType::Type, TSharedPtr<MenuGroup>> MenuMap;
	//��Ϸ����Widgetָ��
	TSharedPtr<SSlAiGameOptionWidget> GameOptionWidget;
	//����Ϸ�ռ�ָ��
	TSharedPtr<SSlAiNewGameWidget> NewGameWidget;
	//ѡ��浵�ռ�ָ��
	TSharedPtr<SSlAiChooseRecordWidget> ChooseRecordWidget;

	//����������
	FCurveSequence MenuAnimation;
	//���߿�����
	FCurveHandle MenuCurve;
	//���������µĸ߶�
	float CurrentHeight;
	//�Ƿ��Ѿ���ʾMenu���
	bool IsMenuShow;
	//�Ƿ���ס��ť
	bool ControlLocked;
	//���浱ǰ�Ķ���״̬
	EMenuAnim::Type AnimState;
	//���浱ǰ�Ĳ˵�
	EMenuType::Type CurrentMenu;
};
