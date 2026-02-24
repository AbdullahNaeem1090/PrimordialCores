// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "PCAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class PRIMORDIALCORES_API UPCAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void GiveStartUpAbilities(TArray<TSubclassOf<UGameplayAbility>> AbilityClass,float Level);
	void AbilityInputPress(const FGameplayTag& AbilityTag);
	void AbilityInputRelease(const FGameplayTag& AbilityTag);
	
};
