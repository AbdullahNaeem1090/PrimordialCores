#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

struct FPCGameplayTags
{
public:
	static const FPCGameplayTags&  Get(){return GameplayTags;}
	static void InitializeNativeGameplayTags();
	
	
	//Attributes Tag
	FGameplayTag Attributes_Vital_Health;
	FGameplayTag Attributes_Vital_Mana;
	
	FGameplayTag Attributes_Primary_Power;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Agility;
	FGameplayTag Attributes_Primary_Vigor;

	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResilience;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;
	
	FGameplayTag Attributes_Resistance_Fire;
	FGameplayTag Attributes_Resistance_Lightening;
	FGameplayTag Attributes_Resistance_Air;
	FGameplayTag Attributes_Resistance_Water;
	FGameplayTag Attributes_Resistance_Earth;
	
	//Powers Tag
	
	FGameplayTag Power;
	
	FGameplayTag Power_Basic;
	FGameplayTag Power_Fire;
	FGameplayTag Power_Earth;
	FGameplayTag Power_Air;
	FGameplayTag Power_Water;
	
	//Combat Tags
	FGameplayTag Combat;
	FGameplayTag Combat_CombatMode;
	FGameplayTag Combat_CombatMode_Melee;
	FGameplayTag Combat_CombatMode_Physical;
	FGameplayTag Combat_Blocking;
	FGameplayTag Combat_HitReacting;
	
	
	// Abilities Tag
	FGameplayTag Ability;
	FGameplayTag Ability_Combat;
	FGameplayTag Ability_Combat_Physical_Punch;
	FGameplayTag Ability_Combat_Physical_Kick;
	FGameplayTag Ability_Combat_Physical_SpecialAttack;
	
	FGameplayTag Ability_HitReact;
	
	//Input Tag
	FGameplayTag Input_LMB;
	FGameplayTag Input_LMB_Hold;
	FGameplayTag Input_RMB;
	FGameplayTag Input_RMB_Hold;
	FGameplayTag Input_LMB_Shift;
	FGameplayTag Input_LMB_Ctrl;
	FGameplayTag Input_LMB_Shift_Ctrl;
	FGameplayTag Input_RMB_Shift;
	FGameplayTag Input_RMB_Ctrl;
	FGameplayTag Input_RMB_Shift_Ctrl;

	//Attack
	FGameplayTag Attack_Light;
	FGameplayTag Attack_Medium;
	FGameplayTag Attack_Heavy;
	FGameplayTag Attack_Launcher;
	FGameplayTag Attack_Knockback;
	
	//Events
	FGameplayTag Event;
	FGameplayTag Event_HitReact;
	
	//Damage
	FGameplayTag Damage_Data;
	
	
private:
	static FPCGameplayTags GameplayTags;
};



