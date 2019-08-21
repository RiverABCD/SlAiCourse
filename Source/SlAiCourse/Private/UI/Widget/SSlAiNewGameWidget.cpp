// Fill out your copyright notice in the Description page of Project Settings.

#include "SSlAiNewGameWidget.h"
#include "SlateOptMacros.h"
#include "SBox.h"
#include "STextBlock.h"
#include "SOverlay.h"
#include "SEditableTextBox.h"

#include "SlAiStyle.h"
#include "SlAiMenuWidgetStyle.h"
#include "SlAiDataHandle.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiNewGameWidget::Construct(const FArguments& InArgs)
{
	//获取编辑器的MenuStyle
	MenuStyle = &SlAiStyle::Get().GetWidgetStyle < FSlAiMenuStyle >("BPSlAiMenuStyle");

	
	ChildSlot
		[
			SNew(SBox).WidthOverride(500.f).HeightOverride(100.f)
			[
				SNew(SOverlay)
				+ SOverlay::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill)
					[
						SNew(SImage).Image(&MenuStyle->MenuItemBrush)
					]
				+ SOverlay::Slot().HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(FMargin(20.f, 0.f, 0.f, 0.f))
					[
						SNew(STextBlock).Font(MenuStyle->Font_40).Text(NSLOCTEXT("SlAiMenu", "NewGame", "NewGame"))
					]
				+ SOverlay::Slot().HAlign(HAlign_Right).VAlign(VAlign_Center).Padding(FMargin(0.f, 0.f, 20.f, 0.f))
					[
						SNew(SBox).WidthOverride(300.f).HeightOverride(60.f)
						[
							SAssignNew(EditTextBox, SEditableTextBox).HintText(NSLOCTEXT("SlAiMenu", "RecordNameHint", "Input Record Name!")).Font(MenuStyle->Font_30)
						]
					]


			]

		];
	
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

bool SSlAiNewGameWidget::AllowEnterGame()
{
	//获取输入的新存档名
	FText InputText = EditTextBox->GetText();
	//文字是否为空
	if (InputText.ToString().IsEmpty()) return false;
	//查询是否存在存档
	for (TArray<FString>::TIterator It(SlAiDataHandle::Get()->RecordDataList); It; ++It) {
		if ((*It).Equals(InputText.ToString())) {
			//设置TextBox为空
			EditTextBox->SetText(FText::FromString(""));
			//修改Hint为存档名重复
			EditTextBox->SetHintText(NSLOCTEXT("SlAiMenu", "NameRepeatedHint", "Record Name Repeated!"));
			//返回false
			return false;
		}
	}
	//保存新的存档名
	SlAiDataHandle::Get()->RecordName = InputText.ToString();
	//返回true;
	return true;
}
