// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SlAiTypes.h"
#include "SlAiPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SLAICOURSE_API ASlAiPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASlAiPlayerController();

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupInputComponent() override;

public:
	//��ȡ��ҽ�ɫ
	class ASlAiPlayerCharacter* SPCharacter;

protected:
	virtual void BeginPlay() override;
	
private:
	//�л��ӽ�
	void ChangeView();

	//��갴���¼�
	void LeftEventStart();
	void LeftEventStop();
	void RightEventStart();
	void RightEventStop();

private:

	//���Ԥ����
	EUpperBody::Type LeftUpperType;

	//�Ҽ�Ԥ����
	EUpperBody::Type RightUpperType;
};
