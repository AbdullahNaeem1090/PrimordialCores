// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/PCAbilitySystemGlobals.h"

#include "GAS/Effects/PCEffectContext.h"

FGameplayEffectContext* UPCAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	UE_LOG(LogTemp, Log, TEXT("PCAbilitySystemGlobals: Allocating FPCEffectContext"));
	return new FPCEffectContext();
}
