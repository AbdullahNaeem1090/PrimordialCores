// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PCBpFunctionLibrary.generated.h"

struct FPhysicalAttackData;
enum class EHitZone : uint8;
enum class ECardinalDirection : uint8;
struct FGameplayEffectContextHandle;
class UGameplayEffect;
class UAbilitySystemComponent;

UCLASS()
class PRIMORDIALCORES_API UPCBpFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable, Category="PC Function Library")
	static void ApplyDamageEffectToTarget(
		TSubclassOf<UGameplayEffect> EffectClass,
		AActor* SourceActor,
		UAbilitySystemComponent* TargetAsc ,
		FGameplayTag InHitType,
		const FHitResult& HitResult, 
		float BaseDamage,
		float Level=1
		);
	
	UFUNCTION(BlueprintCallable, Category="PC Function Library")
	static bool GetHitResultFromEffectContext(const FGameplayEffectContextHandle& Handle,FHitResult& OutHitResult,FGameplayTag& OutHitType);

	UFUNCTION(BlueprintCallable, Category="PC Function Library")
	static UAnimMontage* GetHitReactAnimMontageFromTable(FGameplayTag AttackType,ECardinalDirection HitDirection,EHitZone HitZone,const UDataTable* HitReactTable);

	UFUNCTION(BlueprintCallable, Category="PC Function Library")
	static UAnimMontage* GetDeathMontageFromTable(FGameplayTag HitType,ECardinalDirection HitDirection,const UDataTable* HitReactTable);
	
	UFUNCTION(
		BlueprintCallable,
		Category="PC Function Library",
		meta=(AutoCreateRefTerm="AttackTypes",ToolTip="If InRadius > 0, attacks are filtered by distance. If <= 0, distance check is ignored.")
	)
	static FPhysicalAttackData GetRandomAttackInfo(
		const UDataTable* AttackDataTable,
		const FGameplayTagContainer& AttackTypes,
		bool& bFound);

	UFUNCTION(BlueprintCallable, Category="PC Function Library")
	static FPhysicalAttackData GetAttackInfoBySlot(
		const UDataTable* AttackDataTable,
		FName Slot,
		bool& bFound);

	UFUNCTION(BlueprintCallable, Category="PC Function Library")
	static FPhysicalAttackData GetAttackInfoByName(
		const UDataTable* AttackDataTable,
		FName Name,
		bool& bFound);
	
	UFUNCTION(BlueprintCallable, Category="PC Function Library")
	static ECardinalDirection GetCardinalDirection(const AActor* Victim,const FVector& AttackerLocation);

};
