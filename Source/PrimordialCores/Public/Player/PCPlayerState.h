// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "PCPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
/**
 * 
 */
UCLASS()
class PRIMORDIALCORES_API APCPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	
	APCPlayerState();
	
	UAbilitySystemComponent* GetAbilitySystemComponent() const { return ASC; }
	UAttributeSet* GetAttributeSet() const { return AS; }

public:
	UPROPERTY()
	int32 Level=1;
	
private:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> ASC;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AS;
	
	
};
