// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "PairedAnimAttackInfo.generated.h"

USTRUCT(BlueprintType)
struct FPairedAnimInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag InputTag=FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> AttackAnim=nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> VictimAnim=nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float IdealDistance=0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DistanceTolerance=0.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MinAngle=0.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxAngle=0.f;

};

UCLASS()
class PRIMORDIALCORES_API UPairedAnimAttackInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FPairedAnimInfo GetRandomPairAnimInfoForTag(FGameplayTag InTag) const ;
	
private:
	UPROPERTY(EditDefaultsOnly)
	TArray<FPairedAnimInfo> PairedAnimInfoArray;
};
