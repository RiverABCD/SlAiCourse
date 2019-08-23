// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiPlayerCharacter.h"
#include <ConstructorHelpers.h>
#include <Engine/SkeletalMesh.h>
#include <Components/SkeletalMeshComponent.h>
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASlAiPlayerCharacter::ASlAiPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//��ʼ����������ײ������ΪPlayerProfile,����Ĺ���ģ�͵���ײ�Ͷ���������Ϊ����ײ
	GetCapsuleComponent()->SetCollisionProfileName(FName("PlayerProfile"));

	//��ӵ�һ�˳ƹ���ģ��
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> StaticMeshFirst(TEXT("SkeletalMesh'/Game/Res/PolygonAdventure/Mannequin/FirstPlayer/SkMesh/FirstPlayer.FirstPlayer'"));
	MeshFirst = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshFirst"));
	MeshFirst->SetSkeletalMesh(StaticMeshFirst.Object);
	MeshFirst->SetupAttachment((USceneComponent*)GetCapsuleComponent());
	MeshFirst->bOnlyOwnerSee = true;
	MeshFirst->bReceivesDecals = false;
	//����Ƶ��˥��

	//������ײ����
	MeshFirst->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshFirst->SetCollisionObjectType(ECC_Pawn);
	MeshFirst->SetCollisionResponseToAllChannels(ECR_Ignore);
	//����λ��
	MeshFirst->SetRelativeLocation(FVector(0.f, 0.f, -95.f));
	MeshFirst->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0.f, 0.f, -90.f)));

	//��ȡ��һ�˳ƵĶ�����ͼ
	static ConstructorHelpers::FClassFinder<UAnimInstance> StaticAnimFirst(TEXT("AnimBlueprint'/Game/Blueprint/Player/FirstPlayer_Animation.FirstPlayer_Animation_C'"));
	MeshFirst->AnimClass = StaticAnimFirst.Class;

	//��Ĭ��mesh��ӹ���ģ��
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> StaticMeshThird(TEXT("SkeletalMesh'/Game/Res/PolygonAdventure/Mannequin/Player/SkMesh/Player.Player'"));
	GetMesh()->SetSkeletalMesh(StaticMeshThird.Object);
	GetMesh()->bOnlyOwnerSee = true;
	GetMesh()->bReceivesDecals = false;
	GetMesh()->SetCollisionObjectType(ECC_Pawn);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -95.f));
	GetMesh()->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0.f, 0.f, -90.f)));

	//��ȡ�����˳ƵĶ�����ͼ
	static ConstructorHelpers::FClassFinder<UAnimInstance> StaticAnimThird(TEXT("AnimBlueprint'/Game/Blueprint/Player/ThirdPlayer_Animation.ThirdPlayer_Animation_C'"));
	GetMesh()->AnimClass = StaticAnimThird.Class;

	//������ֱ�
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	//���þ���
	CameraBoom->TargetArmLength = 300.f;
	//����ƫ��
	CameraBoom->TargetOffset = FVector(0.f, 0.f, 60.f);
	//��Controller����ת
	CameraBoom->bUsePawnControlRotation = true;

	//��ʼ�������˳������
	ThirdCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdCamera"));
	ThirdCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	//����ThirdCamera���������������ת
	ThirdCamera->bUsePawnControlRotation = false;

	//��ʼ����һ�˳������
	FirstCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstCamera"));
	FirstCamera->SetupAttachment((USceneComponent*)GetCapsuleComponent());
	//���ø���Controller��ת
	FirstCamera->bUsePawnControlRotation = true;
	//����ƫ��
	FirstCamera->AddLocalOffset(FVector(0.f, 0.f, 60.f));

	//Ĭ�ϵ����˳�
	FirstCamera->SetActive(false);
	ThirdCamera->SetActive(true);
	//����ʾ��һ�˳�ģ��
	GetMesh()->SetOwnerNoSee(false);
	MeshFirst->SetOwnerNoSee(true);


	//��ʼ������
	BaseLookUpRate = 45.f;
	BaseTurnRate = 45.f;

	//���ó�ʼ�ٶ�Ϊ150.f
	GetCharacterMovement()->MaxWalkSpeed = 450.f;
	//��ʼ��Ϊ�����˳�
	GameView = EGameViewMode::Third;
	//�ϰ�������ʼ��Ϊ�޶���
	UpperType = EUpperBody::None;
	//��ʼ��Ϊ�����л��ӽ�
	IsAllowSwitch = true;
}

// Called when the game starts or when spawned
void ASlAiPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASlAiPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASlAiPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &ASlAiPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASlAiPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ASlAiPlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ASlAiPlayerCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis("TurnRate", this, &ASlAiPlayerCharacter::TurnAtRate);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASlAiPlayerCharacter::OnStartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ASlAiPlayerCharacter::OnStopJump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASlAiPlayerCharacter::OnStartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASlAiPlayerCharacter::OnStopRun);

}

void ASlAiPlayerCharacter::ChangeView(EGameViewMode::Type NewGameView)
{
	GameView = NewGameView;
	switch (GameView)
	{
	case EGameViewMode::First:
		FirstCamera->SetActive(true);
		ThirdCamera->SetActive(false);
		MeshFirst->SetOwnerNoSee(false);
		GetMesh()->SetOwnerNoSee(true);
		//�޸�handobject�󶨵�λ��
		//HandObject->AttachToComponent(MeshFirst, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RHSocket"));
		break;
	case EGameViewMode::Third:
		FirstCamera->SetActive(false);
		ThirdCamera->SetActive(true);
		MeshFirst->SetOwnerNoSee(true);
		GetMesh()->SetOwnerNoSee(false);
		//�޸�handobject�󶨵�λ��
		//HandObject->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RHSocket"));
		break;
	}
}

void ASlAiPlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.f&&Controller) {
		const FRotator Rotation = Controller->GetControlRotation();
		FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ASlAiPlayerCharacter::MoveRight(float Value)
{
	if (Value != 0) {
		const FQuat Rotation = GetActorQuat();
		FVector Direction = FQuatRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ASlAiPlayerCharacter::LookUpAtRate(float Value)
{
	AddControllerPitchInput(Value*BaseLookUpRate*GetWorld()->GetDeltaSeconds());
}

void ASlAiPlayerCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ASlAiPlayerCharacter::TurnAtRate(float Value)
{
	AddControllerYawInput(Value*BaseTurnRate*GetWorld()->GetDeltaSeconds());
}

void ASlAiPlayerCharacter::OnStartJump()
{
	//bPressJump = true;
}

void ASlAiPlayerCharacter::OnStopJump()
{
}

void ASlAiPlayerCharacter::OnStartRun()
{
}

void ASlAiPlayerCharacter::OnStopRun()
{
}

