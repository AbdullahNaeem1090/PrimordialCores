// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "HitReactBoneConfig.generated.h"

UENUM(BlueprintType)
enum class EHitZone : uint8
{
	Head,
	Torso,
	LeftArm,
	RightArm,
	LeftLeg,
	RightLeg,
	Pelvis,
	Default
};

UENUM(BlueprintType)
enum class ECardinalDirection : uint8
{
	Front,
	Back,
	Left,
	Right
};

USTRUCT(BlueprintType)
struct FPCHitReactRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag HitType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EHitZone HitZone;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ECardinalDirection HitDirection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> HitReactMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName MontageSlot = FName("Default");

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float PlayRate = 1.f;
};

UCLASS()
class PRIMORDIALCORES_API UHitReactBoneConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	EHitZone GetZoneForBone(FName BoneName, USkeletalMeshComponent* Mesh) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<FName, EHitZone> BoneToZoneMap;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EHitZone DefaultZone = EHitZone::Torso;

};
