// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/PCBaseGameplayAbility.h"
#include "PhysicalSimpleAbility.generated.h"

/**
 * 
 */
UCLASS()
class PRIMORDIALCORES_API UPhysicalSimpleAbility : public UPCBaseGameplayAbility
{
	GENERATED_BODY()
	
	
public:
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnInputPressed();
};
