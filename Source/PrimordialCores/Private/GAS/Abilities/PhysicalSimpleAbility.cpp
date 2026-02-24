// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/PhysicalSimpleAbility.h"

void UPhysicalSimpleAbility::InputPressed(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	OnInputPressed();
}
