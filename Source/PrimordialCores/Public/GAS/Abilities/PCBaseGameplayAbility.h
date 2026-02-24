// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "PCBaseGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class PRIMORDIALCORES_API UPCBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="PC")
	FGameplayTag InputTag;
	
};
