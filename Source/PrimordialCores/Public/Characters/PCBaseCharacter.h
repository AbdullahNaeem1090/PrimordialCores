// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interfaces/CombatInterface.h"
#include "PCBaseCharacter.generated.h"

class UHitReactBoneConfig;
class UAttributeSet;
class UAbilitySystemComponent;
class UGameplayAbility;
class UGameplayEffect;

UCLASS()
class PRIMORDIALCORES_API APCBaseCharacter : public ACharacter,public IAbilitySystemInterface,public ICombatInterface
{
	GENERATED_BODY()

public:
	APCBaseCharacter();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	//Combat Interface
	virtual FVector GetSocketLocationByName_Implementation(FName SocketName) override;
	virtual UDataTable* GetHitReactDataTable_Implementation() override;
	virtual void Death_Implementation(FVector HitLocation, FGameplayTag HitType) override;
	virtual void FillHitReactInfo_Implementation(FVector HitLocation, FName Bone, ECardinalDirection& HitDirection, EHitZone& HitZone) override;

protected:
	
	virtual void BeginPlay() override;
	virtual void InitializeAttributes();
	void ApplyAttributeInitEffect(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;
	void GrantStartUpAbilities(float Level) const;
	void OnDeathMontageBlendingOut(UAnimMontage* Montage,bool bInterrupted);
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> ASC;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AS;
	
	UPROPERTY(EditDefaultsOnly ,Category="PC|Attributes")
	TSubclassOf<UGameplayEffect> VitalAttributes;	
	
	UPROPERTY(EditDefaultsOnly ,Category="PC|Attributes")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;
	
	UPROPERTY(EditDefaultsOnly ,Category="PC|Attributes")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;
	
	UPROPERTY(EditDefaultsOnly ,Category="PC|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartUpAbilities;

public:	
	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditDefaultsOnly, Category="PC|Data")
	TObjectPtr<UDataTable> DeathMontageTable=nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category="PC|Data")
	TObjectPtr<UDataTable> HitReactTable=nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category="PC|Data")
	TObjectPtr<UHitReactBoneConfig> BonesToZonesDataAsset=nullptr;
};
