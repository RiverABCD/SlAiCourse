// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiCourse.h"
#include "Modules/ModuleManager.h"
#include "SlAiStyle.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FSlAiCourseModule, SlAiCourse, "SlAiCourse" );

void FSlAiCourseModule::StartupModule()
{
	//��ʼ����ʽ
	FSlateStyleRegistry::UnRegisterSlateStyle(SlAiStyle::GetStyleSetName());
	SlAiStyle::Initialize();
}

void FSlAiCourseModule::ShutdownModule()
{
	SlAiStyle::ShutDown();
}
