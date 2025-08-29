﻿// Fill out your copyright notice in the Description page of Project Settings.
#include "UBaseElementSkill.h"

#include "Sonheim/AreaObject/Base/AreaObject.h"
#include "Sonheim/Element/BaseElement.h"
#include "Sonheim/Utilities/LogMacro.h"

void UUBaseElementSkill::OnCastStart(class AAreaObject* Caster, AAreaObject* Target)
{
	IsFired = false;
	Super::OnCastStart(Caster, Target);
}

void UUBaseElementSkill::OnCastFire()
{
	if (IsFired) return;
	Super::OnCastFire();
}

void UUBaseElementSkill::Client_OnCastFire()
{
	Super::Client_OnCastFire();
}

void UUBaseElementSkill::Server_OnCastFire()
{
	Super::Server_OnCastFire();
	FireElement();
}

void UUBaseElementSkill::FireElement()
{
	IsFired = true;
	// Data Table에서 셋팅했으면 셋팅 하기
	if (m_SkillData->ElementClass != nullptr)
	{
		ElementClass = m_SkillData->ElementClass;
	}
	ABaseElement* SpawnedElement
	{
		GetWorld()->SpawnActor<ABaseElement>(ElementClass, m_Caster->GetActorLocation(), m_Caster->GetActorRotation())
	};

	// ToDo : Notify에서 Index 주입
	FAttackData* AttackData = GetAttackDataByIndex(0);

	m_TargetPos = m_Caster == m_Target
		              ? m_Caster->GetActorLocation() + m_Caster->GetActorForwardVector() * 800
		              : m_Target->GetActorLocation();

	if (SpawnedElement)
	{
		SpawnedElement->SetOwner(m_Caster);
		SpawnedElement->InitElement(m_Caster, m_Target, m_TargetPos, AttackData);
	}
	else
	{
		FLog::Log("No SpawnedSandBlast");
	}
}
