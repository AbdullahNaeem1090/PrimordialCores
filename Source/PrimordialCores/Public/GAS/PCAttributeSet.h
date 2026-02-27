// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PCAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

UCLASS()
class PRIMORDIALCORES_API UPCAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	
	// Vital 
	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UPCAttributeSet, Health);
	
	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UPCAttributeSet, Mana);
	
	// Primary 
	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Power;
	ATTRIBUTE_ACCESSORS(UPCAttributeSet, Power); 
	
	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UPCAttributeSet, Resilience); 
	
	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Agility;
	ATTRIBUTE_ACCESSORS(UPCAttributeSet, Agility); 
	
	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UPCAttributeSet, Vigor); 
	
	//Secondary
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UPCAttributeSet, Armor);
	
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UPCAttributeSet, ArmorPenetration);

	// UPROPERTY(BlueprintReadOnly,  Category = "Secondary Attributes")
	// FGameplayAttributeData BlockChance;
	// ATTRIBUTE_ACCESSORS(UPCAttributeSet, BlockChance);

	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UPCAttributeSet, CriticalHitChance);
 
	UPROPERTY(BlueprintReadOnly,  Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UPCAttributeSet, CriticalHitDamage);

	UPROPERTY(BlueprintReadOnly,  Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitResilience;
	ATTRIBUTE_ACCESSORS(UPCAttributeSet, CriticalHitResilience);

	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UPCAttributeSet, HealthRegeneration);

	UPROPERTY(BlueprintReadOnly,  Category = "Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UPCAttributeSet, ManaRegeneration);

	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UPCAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UPCAttributeSet, MaxMana);

	// Resistance Attributes
	
	UPROPERTY(BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData FireResistance;
	ATTRIBUTE_ACCESSORS(UPCAttributeSet, FireResistance);
	
	UPROPERTY(BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData LighteningResistance;
	ATTRIBUTE_ACCESSORS(UPCAttributeSet, LighteningResistance);
	
	UPROPERTY(BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData AirResistance;
	ATTRIBUTE_ACCESSORS(UPCAttributeSet, AirResistance);
	
	UPROPERTY(BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData WaterResistance;
	ATTRIBUTE_ACCESSORS(UPCAttributeSet, WaterResistance);
	
	UPROPERTY(BlueprintReadOnly, Category = "Resistance Attributes")
	FGameplayAttributeData EarthResistance;
	ATTRIBUTE_ACCESSORS(UPCAttributeSet, EarthResistance);
	
	//Temp ATtributes
	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UPCAttributeSet, IncomingDamage);
private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
void SendHitReactEvent(FEffectProperties& Props);
};

