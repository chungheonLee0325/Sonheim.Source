﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "GumossFSM.h"

#include "Sonheim/AreaObject/Monster/BaseMonster.h"
#include "Sonheim/AreaObject/Monster/AI/Derived/AiMonster/BaseCombatAiState/AttackMode.h"
#include "Sonheim/AreaObject/Monster/AI/Derived/AiMonster/BaseCombatAiState/Chase.h"
#include "Sonheim/AreaObject/Monster/AI/Derived/AiMonster/BaseCombatAiState/PatrolMode.h"
#include "Sonheim/AreaObject/Monster/AI/Derived/AiMonster/BaseCombatAiState/PutDistance.h"
#include "Sonheim/AreaObject/Monster/AI/Derived/AiMonster/BaseCombatAiState/SelectMode.h"
#include "Sonheim/AreaObject/Monster/AI/Derived/AiMonster/BaseCombatAiState/UseSkill.h"
#include "Sonheim/AreaObject/Monster/AI/Derived/AiMonster/BasePartnerAiState/PartnerPatrolMode.h"


// Sets default values for this component's properties
UGumossFSM::UGumossFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGumossFSM::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGumossFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGumossFSM::InitStatePool()
{
	// PartnerPatrolMode 
	auto PartnerPatrolMode = CreateState<UPartnerPatrolMode>(this, m_Owner,EAiStateType::PartnerSkillMode, EAiStateType::SelectMode);
	AddState(EAiStateType::PartnerPatrolMode, PartnerPatrolMode);
	
	// PatrolMode
	// auto PatrolMode = CreateState<UPatrolMode>(this, m_Owner, EAiStateType::SelectMode);
	// AddState(EAiStateType::PatrolMode, PatrolMode);

	// SelectMode 
	auto SelectMode = CreateState<USelectMode>(this, m_Owner,EAiStateType::AttackMode, EAiStateType::None, EAiStateType::PartnerPatrolMode);
	AddState(EAiStateType::SelectMode, SelectMode);

	// AttackMode 
	auto AttackMode = CreateState<UAttackMode>(this, m_Owner,EAiStateType::PutDistance, EAiStateType::UseSkill, EAiStateType::Chase);
	AttackMode->SetSkillRoulette(m_Owner->GetSkillRoulette());
	AddState(EAiStateType::AttackMode, AttackMode);

	// Chase 
	auto Chase = CreateState<UChase>(this, m_Owner,EAiStateType::PartnerPatrolMode, EAiStateType::UseSkill);
	AddState(EAiStateType::Chase, Chase);

	// PutDistance 
	auto PutDistance = CreateState<UPutDistance>(this, m_Owner,EAiStateType::UseSkill);
	AddState(EAiStateType::PutDistance, PutDistance);

	// UseSkill 
	auto UseSkill = CreateState<UUseSkill>(this, m_Owner,EAiStateType::SelectMode);
	AddState(EAiStateType::UseSkill, UseSkill);

	// 시작 State
	ChangeState(EAiStateType::PartnerPatrolMode);
}

