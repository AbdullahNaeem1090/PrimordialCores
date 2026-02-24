// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Data/AbilityInputConfig.h"

FGameplayTag UAbilityInputConfig::GetAbilityTagForInputTag(const FGameplayTag& InputTag, const FGameplayTag& PowerTag,
	const FGameplayTag& CombatTag) const
{
	for (auto Index : InputToAbilityTagsArray)
	{
		if (InputTag == Index.InputTag && PowerTag == Index.PowerTag && CombatTag == Index.CombatTag)
			return Index.AbilityTag;
	}
	return FGameplayTag();
}
