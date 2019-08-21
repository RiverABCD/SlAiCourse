// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Engine/GameEngine.h"
#include "SlateApplication.h"
#include "Engine/GameEngine.h"
#include "SlateSound.h"
#include "TimerManager.h"

namespace SlAiHelper{
	FORCEINLINE void Debug(FString Message,float Duration = 3.0f)
	{
		if(GEngine)
		{ 
			GEngine->AddOnScreenDebugMessage(-1, Duration, FColor::Red, Message);
		}
	}

	template<class UserClass>
	FORCEINLINE FTimerHandle PlayerSoundAndCall(UWorld* World, const FSlateSound Sound, UserClass* InUserObject, typename FTimerDelegate::TRawMethodDelegate<UserClass>::FMethodPtr InMethod)
	{
		FSlateApplication::Get().PlaySound(Sound);
		FTimerHandle Result;
		const float SoundDuration = FMath::Max(FSlateApplication::Get().GetSoundDuration(Sound), 0.1f);
		FTimerDelegate CallBack;
		CallBack.BindRaw(InUserObject, InMethod);
		World->GetTimerManager().SetTimer(Result, CallBack, SoundDuration, false);
		return Result;
	}
};

