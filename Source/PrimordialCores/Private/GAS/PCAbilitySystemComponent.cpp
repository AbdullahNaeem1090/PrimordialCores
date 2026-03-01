// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/PCAbilitySystemComponent.h"

#include "GAS/Abilities/PCBaseGameplayAbility.h"

void UPCAbilitySystemComponent::GiveStartUpAbilities(TArray<TSubclassOf<UGameplayAbility>> AbilityClasses, float Level)
{
	for (TSubclassOf<UGameplayAbility> AbilityClass : AbilityClasses)
	{
		FGameplayAbilitySpec AbilitySpec(AbilityClass,Level);
		if (const UPCBaseGameplayAbility* AuraAbility = Cast<UPCBaseGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(AuraAbility->InputTag);
			GiveAbility(AbilitySpec);
		}else
		{
			GiveAbility(AbilitySpec);
		}
	}
}

void UPCAbilitySystemComponent::AbilityInputRelease(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	
	for (FGameplayAbilitySpec& AbilitySpec:GetActivatableAbilities())
	{
	  if (AbilitySpec.GetDynamicSpecSourceTags().HasTag(InputTag))
	  	AbilitySpecInputReleased(AbilitySpec);
		
		UGameplayAbility* PrimaryInstance = AbilitySpec.GetPrimaryInstance();
		if (PrimaryInstance)
		{
			InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, AbilitySpec.Handle, PrimaryInstance->GetCurrentActivationInfo().GetActivationPredictionKey());
		}
	}
}

void UPCAbilitySystemComponent::AbilityInputPress(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
    
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive()) 
				TryActivateAbility(AbilitySpec.Handle);
			else
			{
				UGameplayAbility* PrimaryInstance = AbilitySpec.GetPrimaryInstance();
				if (PrimaryInstance)
				{
					InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, AbilitySpec.Handle, PrimaryInstance->GetCurrentActivationInfo().GetActivationPredictionKey());
				}
			}
		}
	}
}