﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sonheim/Element/BaseElement.h"
#include "BladeWind.generated.h"

UCLASS()
class SONHEIM_API ABladeWind : public ABaseElement
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABladeWind();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// fire actor
	virtual void InitElement(AAreaObject* Caster, AAreaObject* Target, const FVector& TargetLocation,
	                         FAttackData* AttackData) override;

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	                            AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp,
	                            int32 OtherBodyIndex,
	                            bool bFromSweep,
	                            const FHitResult& SweepResult) override;

	virtual void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                            FVector NormalImpulse, const FHitResult& Hit) override;
};
