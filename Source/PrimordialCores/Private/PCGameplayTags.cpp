#include "PCGameplayTags.h" 
#include "GameplayTagsManager.h"


FPCGameplayTags FPCGameplayTags::GameplayTags;

void FPCGameplayTags::InitializeNativeGameplayTags()
 {
	//vital attributes
	GameplayTags.Attributes_Vital_Health =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Vital.Health"),
		TEXT("Current health of the character. When it reaches zero, the character is defeated.")
	);

	GameplayTags.Attributes_Vital_Mana =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Vital.Mana"),
		TEXT("Current mana resource used to activate abilities.")
	);

	//primary attributes
	
	GameplayTags.Attributes_Primary_Power =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Primary.Power"),
	TEXT("Increases overall damage output, elemental scaling, and armor penetration.")
	);
	
	GameplayTags.Attributes_Primary_Resilience =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Primary.Resilience"),
	TEXT("Increases defensive effectiveness, critical hit resistance, and control resistance.")
	);

	GameplayTags.Attributes_Primary_Agility =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Agility"),
		TEXT("Increases movement speed, cast speed, critical hit chance, and evasion.")
	);

	GameplayTags.Attributes_Primary_Vigor =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Vigor"),
		TEXT("Increases maximum health, stamina, and regeneration rates.")
	);
	
	
	// secondary attributes
	GameplayTags.Attributes_Secondary_Armor =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("Attributes.Secondary.Armor"),
    TEXT("Reduces incoming physical damage before other resistances are applied.")
);

	GameplayTags.Attributes_Secondary_ArmorPenetration =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
	    FName("Attributes.Secondary.ArmorPenetration"),
	    TEXT("Ignores a portion of the target's armor when dealing physical damage.")
	);

	// GameplayTags.Attributes_Secondary_BlockChance =
	// UGameplayTagsManager::Get().AddNativeGameplayTag(
	//     FName("Attributes.Secondary.BlockChance"),
	//     TEXT("Chance to partially or fully block incoming damage from an attack.")
	// );

	GameplayTags.Attributes_Secondary_CriticalHitChance =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
	    FName("Attributes.Secondary.CriticalHitChance"),
	    TEXT("Chance for attacks to deal critical damage.")
	);

	GameplayTags.Attributes_Secondary_CriticalHitDamage =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
	    FName("Attributes.Secondary.CriticalHitDamage"),
	    TEXT("Multiplier applied to damage when a critical hit occurs.")
	);

	GameplayTags.Attributes_Secondary_CriticalHitResilience =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
	    FName("Attributes.Secondary.CriticalHitResilience"),
	    TEXT("Reduces bonus damage taken from enemy critical hits.")
	);

	GameplayTags.Attributes_Secondary_HealthRegeneration =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
	    FName("Attributes.Secondary.HealthRegeneration"),
	    TEXT("Amount of health restored per second.")
	);

	GameplayTags.Attributes_Secondary_ManaRegeneration =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
	    FName("Attributes.Secondary.ManaRegeneration"),
	    TEXT("Amount of mana restored per second.")
	);

	GameplayTags.Attributes_Secondary_MaxHealth =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
	    FName("Attributes.Secondary.MaxHealth"),
	    TEXT("Maximum health value of the character.")
	);

	GameplayTags.Attributes_Secondary_MaxMana =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
	    FName("Attributes.Secondary.MaxMana"),
	    TEXT("Maximum mana value of the character.")
	);

	// Resistances attributes
		GameplayTags.Attributes_Resistance_Fire =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Fire"),
		TEXT("Reduces damage taken from fire-based attacks.")
	);

	GameplayTags.Attributes_Resistance_Lightening =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Lightning"),
		TEXT("Reduces damage taken from lightning-based attacks.")
	);

	GameplayTags.Attributes_Resistance_Air =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Air"),
		TEXT("Reduces damage taken from air-based attacks.")
	);

	GameplayTags.Attributes_Resistance_Water =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Water"),
		TEXT("Reduces damage taken from water-based attacks.")
	);

	GameplayTags.Attributes_Resistance_Earth =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Earth"),
		TEXT("Reduces damage taken from earth-based attacks.")
	);

	// Powers
	GameplayTags.Power =
UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Power"),
	TEXT("Root tag for all elemental powers.")
);

	GameplayTags.Power_Basic =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Power.Basic"),
		TEXT("Represents non-elemental basic power.")
	);

	GameplayTags.Power_Fire =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Power.Fire"),
		TEXT("Represents fire elemental power.")
	);

	GameplayTags.Power_Earth =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Power.Earth"),
		TEXT("Represents earth elemental power.")
	);

	GameplayTags.Power_Air =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Power.Air"),
		TEXT("Represents air elemental power.")
	);

	GameplayTags.Power_Water =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Power.Water"),
		TEXT("Represents water elemental power.")
	);
	
// Combat Mode	
	GameplayTags.Combat =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Combat"),
		TEXT("Root tag for all combat related states and classifications.")
	);

	GameplayTags.Combat_CombatMode =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Combat.CombatMode"),
		TEXT("Root tag for combat modes.")
	);

	GameplayTags.Combat_CombatMode_Melee =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Combat.CombatMode.Melee"),
		TEXT("Close-range melee combat mode.")
	);

	GameplayTags.Combat_CombatMode_Physical =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Combat.CombatMode.Physical"),
		TEXT("Physical combat mode classification.")
	);

	GameplayTags.Combat_Blocking =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Combat.Blocking"),
		TEXT("Character is currently blocking.")
	);

	GameplayTags.Combat_HitReacting =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Combat.HitReacting"),
		TEXT("Character is currently playing a hit reaction.")
	);
    
// Ability Tags
	GameplayTags.Ability_Combat_Physical_Punch =
UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Ability.Combat.Physical.Punch"),
	TEXT("Basic physical punch attack ability.")
);

	GameplayTags.Ability_Combat_Physical_Kick =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Ability.Combat.Physical.Kick"),
		TEXT("Basic physical kick attack ability.")
	);
	

	GameplayTags.Ability_Combat_Physical_SpecialAttack =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Ability.Combat.Physical.SpecialAttack"),
		TEXT("Special physical attack ability.")
	);
	
	GameplayTags.Ability_HitReact =
UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Ability.HitReact"),
	TEXT("Special physical attack ability.")
);
	
	// input tags
	GameplayTags.Input_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
	   FName("Input.LMB"),
	   TEXT("Left mouse button input")
   );
    
	GameplayTags.Input_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.RMB"),
		TEXT("Right mouse button input")
	);
    
	GameplayTags.Input_LMB_Shift = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.LMB.Shift"),
		TEXT("Left mouse button + Shift modifier")
	);
    
	GameplayTags.Input_LMB_Ctrl = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.LMB.Ctrl"),
		TEXT("Left mouse button + Ctrl modifier")
	);
    
	GameplayTags.Input_LMB_Shift_Ctrl = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.LMB.Shift.Ctrl"),
		TEXT("Left mouse button + Shift + Ctrl modifiers")
	);
    
	GameplayTags.Input_RMB_Shift = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.RMB.Shift"),
		TEXT("Right mouse button + Shift modifier")
	);
    
	GameplayTags.Input_RMB_Ctrl = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.RMB.Ctrl"),
		TEXT("Right mouse button + Ctrl modifier")
	);
    
	GameplayTags.Input_RMB_Shift_Ctrl = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.RMB.Shift.Ctrl"),
		TEXT("Right mouse button + Shift + Ctrl modifiers")
	);
    
//attack tags

	GameplayTags.Attack_Light =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attack.Light"),
		TEXT("Light attack classification.")
	);

	GameplayTags.Attack_Medium =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attack.Medium"),
		TEXT("Medium attack classification.")
	);

	GameplayTags.Attack_Heavy =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attack.Heavy"),
		TEXT("Heavy attack classification.")
	);

	GameplayTags.Attack_Launcher =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attack.Launcher"),
		TEXT("Launcher attack that sends target airborne.")
	);

	GameplayTags.Attack_Knockback =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attack.Knockback"),
		TEXT("Attack that pushes the target backward.")
	);
	
	//Event Tags
	GameplayTags.Event =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Event"),
		TEXT("Attack that pushes the target backward.")
	);
	
	GameplayTags.Event_HitReact =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Event.HitReact"),
		TEXT("Attack that pushes the target backward.")
	);
	
	GameplayTags.Damage_Data =
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Data"),
		TEXT("Base Damage.")
	);
 }
