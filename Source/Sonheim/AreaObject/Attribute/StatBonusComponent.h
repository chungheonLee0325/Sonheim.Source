// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Sonheim/ResourceManager/SonheimGameType.h"
#include "StatBonusComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatChanged, EAreaObjectStatType, StatType);

// 스탯 수정자 적용 방식
UENUM(BlueprintType)
enum class EStatModifierType : uint8
{
	Additive UMETA(DisplayName = "Additive"),           // 더하기
	Multiplicative UMETA(DisplayName = "Multiplicative"), // 곱하기
	Override UMETA(DisplayName = "Override")            // 덮어쓰기
};

// 스탯 수정자 구조체
USTRUCT(BlueprintType)
struct FStatModifier
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAreaObjectStatType StatType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EStatModifierType ModifierType;

	// 보너스 소스 추적용 (아이템, 스킬, 버프 등)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SourceID;

	FStatModifier()
		: StatType(EAreaObjectStatType::HP), Value(0.0f), ModifierType(EStatModifierType::Additive), SourceID(0)
	{
	}

	FStatModifier(EAreaObjectStatType InStatType, float InValue, EStatModifierType InModType, int InSourceID = 0)
		: StatType(InStatType), Value(InValue), ModifierType(InModType), SourceID(InSourceID)
	{
	}
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SONHEIM_API UStatBonusComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UStatBonusComponent();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// 스탯 보너스 추가
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void AddStatBonus(EAreaObjectStatType StatType, float Value, EStatModifierType ModType = EStatModifierType::Additive, int SourceID = 0);
	
	// 스탯 보너스 제거
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void RemoveStatBonus(EAreaObjectStatType StatType, float Value, EStatModifierType ModType = EStatModifierType::Additive, int SourceID = 0);
	
	// 특정 소스 ID에 해당하는 모든 스탯 보너스 추가/제거
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void ApplyItemStatBonuses(int ItemID, bool bApply);
	
	// 최종 스탯 값 계산
	UFUNCTION(BlueprintCallable, Category = "Stats")
	float GetModifiedStatValue(EAreaObjectStatType StatType, float BaseValue);
	
	// 특정 유형의 모든 스탯 보너스 제거
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void ClearAllStatBonuses(EAreaObjectStatType StatType);
	
	// 모든 스탯 보너스 제거
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void ClearAllBonuses();
	
	// 특정 소스의 모든 스탯 보너스 제거
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void RemoveAllBonusesFromSource(int SourceID);

	// 현재 활성화된 무기 슬롯 설정
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void SetCurrentWeaponSlot(EEquipmentSlotType SlotType);
	
	// 아이템 장착 시 무기인지 확인하고 적절히 처리
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void RegisterEquippedItem(EEquipmentSlotType SlotType, int ItemID, bool bEquipping);

	// 현재 적용된 모든 스탯 보너스 가져오기
	UFUNCTION(BlueprintCallable, Category = "Stats")
	TArray<FStatModifier> GetAllStatBonuses() const;

	// 특정 스탯의 모든 보너스 가져오기
	UFUNCTION(BlueprintCallable, Category = "Stats")
	TArray<FStatModifier> GetStatBonuses(EAreaObjectStatType StatType) const;

	// 이벤트 델리게이트
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnStatChanged OnStatChanged;

	// 네트워크 동기화를 위한 델리게이트
	DECLARE_DELEGATE_OneParam(FOnStatBonusChanged, EAreaObjectStatType);
	FOnStatBonusChanged OnStatBonusChangedDelegate;

private:
	// 스탯 유형별 보너스 저장
	TMap<EAreaObjectStatType, TArray<FStatModifier>> StatBonuses;
	
	// 아이템별 적용된 보너스 추적
	TMap<int, TArray<FStatModifier>> ItemStatBonuses;
	
	// 무기 슬롯별 보너스 저장 (무기 슬롯만 별도 관리)
	TMap<EEquipmentSlotType, TArray<FStatModifier>> WeaponSlotBonuses;
	
	// 현재 활성화된 무기 슬롯
	UPROPERTY()
	EEquipmentSlotType CurrentWeaponSlot = EEquipmentSlotType::Weapon1;

	// 메모리 최적화를 위한 정리 함수
	void CleanupEmptyStatArrays();

	// 게임 인스턴스 참조
	UPROPERTY()
	class USonheimGameInstance* GameInstance;
};