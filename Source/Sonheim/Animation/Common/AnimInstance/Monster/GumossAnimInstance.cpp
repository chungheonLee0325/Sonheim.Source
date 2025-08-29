﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "GumossAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Sonheim/AreaObject/Base/AreaObject.h"
#include "Sonheim/AreaObject/Monster/AI/Base/BaseAiFSM.h"
#include "Sonheim/AreaObject/Monster/AI/Base/BaseAiState.h"
#include "Sonheim/AreaObject/Monster/Variants/NormalMonsters/Gumoss/Gumoss.h"

void UGumossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Character{Cast<AGumoss>(m_Owner)};
	if (Character)
	{
		Speed = Character->GetVelocity().Length();
		bIsDead = Character->IsDead;
		bIsJump = Character->GetCharacterMovement()->IsFalling();

		if (Character->m_AiFSM)
		{
			if (Character->m_AiFSM->m_CurrentState)
			{
				State = Character->m_AiFSM->m_CurrentState->AiStateType();
				//LOG_PRINT(TEXT("State : %d"), State);
			}
		}
		else
		{
			//LOG_PRINT(TEXT("No m_AiFSM"));
		}
	}
}
