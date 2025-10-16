// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/WeaponInterface.h"
#include "Sonheim/GameObject/Items/BaseItem.h"
#include "BaseWeapon.generated.h"

UCLASS()
class SONHEIM_API ABaseWeapon : public ABaseItem, public IWeaponInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void HandleLeftButtonPressed() override;
	virtual void HandleRightButtonPressed() override;
};
