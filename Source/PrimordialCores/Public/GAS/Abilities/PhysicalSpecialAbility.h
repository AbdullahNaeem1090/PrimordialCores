// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/PCBaseGameplayAbility.h"
#include "GAS/Data/PairedAnimAttackInfo.h"
#include "PhysicalSpecialAbility.generated.h"

class UPairedAnimAttackInfo;
/**
 * 
 */
UCLASS()
class PRIMORDIALCORES_API UPhysicalSpecialAbility : public UPCBaseGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PC")
	TObjectPtr<UPairedAnimAttackInfo> PairedAnimInfoAsset;
	
	UFUNCTION(BlueprintCallable)
	bool GetAndSetPairedAnimInfo();
	
protected:
	// Add Removal of Motion Warping Function 
	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool IsTargetInIdealRange() const ;
	
	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool TargetIsFacingAttackerInRange(float MinAngle,float MaxAngle)const ;
	
	UPROPERTY(BlueprintReadOnly)
	FPairedAnimInfo PairAnimInfo;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AActor> Attacker;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AActor> Target;
};
