// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PCBpFunctionLibrary.generated.h"

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

};
