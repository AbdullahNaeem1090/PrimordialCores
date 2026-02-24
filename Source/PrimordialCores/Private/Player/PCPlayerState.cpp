// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PCPlayerState.h"
#include "GAS/PCAbilitySystemComponent.h"
#include "GAS/PCAttributeSet.h"

APCPlayerState::APCPlayerState()
{
	ASC = CreateDefaultSubobject<UPCAbilitySystemComponent>("AbilitySystemComponent");
	AS = CreateDefaultSubobject<UPCAttributeSet>("AttributeSet");
}

