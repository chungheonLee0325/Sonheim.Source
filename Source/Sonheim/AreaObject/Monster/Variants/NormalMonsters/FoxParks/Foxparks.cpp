﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Foxparks.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sonheim/AreaObject/Monster/AI/Derived/AiMonster/PalFSM/FoxparksFSM.h"
#include "Sonheim/AreaObject/Player/SonheimPlayer.h"


// Sets default values
AFoxparks::AFoxparks()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	m_AreaObjectID = 106;

	// FSM Setting
	m_AiFSM = AFoxparks::CreateFSM();
	// Skill Setting
	m_SkillRoulette = ABaseMonster::CreateSkillRoulette();
	
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh
	(TEXT("/Script/Engine.SkeletalMesh'/Game/_Resource/Monster/Foxparks/SK_Kitsunebi_LOD0.SK_Kitsunebi_LOD0'"));
	if (TempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -60), FRotator(0, -90, 0));
		GetMesh()->SetRelativeScale3D(FVector(0.5f));
	}
	
	GetCapsuleComponent()->SetCapsuleRadius(60.f);
	GetCapsuleComponent()->SetCapsuleHalfHeight(50.f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
}

// Called when the game starts or when spawned
void AFoxparks::BeginPlay()
{
	Super::BeginPlay();

	// Eye Material
	EyeMat = GetMesh()->CreateDynamicMaterialInstance(2);
	
	if (!HasAuthority())
	{
		m_AiFSM = nullptr;
	}
	// ToDo : 삭제 예정
	// ASonheimPlayer* player = Cast<ASonheimPlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
	// if (player != nullptr)
	// {
	// 	SetPartnerOwner(player);		
	// }
	// else
	// {
	// 	FLog::Log("There Is No Player");
	// }
	bIsCanCalled = true;
	bCanJump = true;
}

// Called every frame
void AFoxparks::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFoxparks::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UBaseAiFSM* AFoxparks::CreateFSM()
{
	return CreateDefaultSubobject<UFoxparksFSM>(TEXT("FSM"));
}