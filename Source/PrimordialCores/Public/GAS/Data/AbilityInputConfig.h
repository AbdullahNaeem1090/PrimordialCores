// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AbilityInputConfig.generated.h"

USTRUCT(BlueprintType)
struct FAbilityInput
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag PowerTag = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag CombatTag = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag AbilityTag = FGameplayTag();
};

UCLASS()
class PRIMORDIALCORES_API UAbilityInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FAbilityInput> InputToAbilityTagsArray;
	
	FGameplayTag GetAbilityTagForInputTag(const FGameplayTag& InputTag,const FGameplayTag& PowerTag,const FGameplayTag& CombatTag) const ;
};
