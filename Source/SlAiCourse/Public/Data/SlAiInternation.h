// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SLAICOURSE_API SlAiInternation
{
public:
	static void Register(FText Value) { return; }
};

#define LOCTEXT_NAMESPACE "SlAiMenu"

SlAiInternation::Register(LOCTEXT("Menu","Menu"));

#undef LOCTEXT_NAMESPACE

//在一个域名空间内的本地化，同上define
//SlAiInternation::Register(NSLOCTEXT("SlAiMenu", "Menu", "Menu"));
