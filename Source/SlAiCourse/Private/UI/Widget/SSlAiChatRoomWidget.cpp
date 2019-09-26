// Fill out your copyright notice in the Description page of Project Settings.

#include "SSlAiChatRoomWidget.h"
#include "SlateOptMacros.h"
#include "SBox.h"
#include "STextBlock.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiChatRoomWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
		[
			SNew(SBox).WidthOverride(300.f).HeightOverride(100.f)
			[
				SNew(STextBlock).Text(FText::FromString("ChatRoom"))
			]
		];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
