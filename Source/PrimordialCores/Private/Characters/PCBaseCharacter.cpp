// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PCBaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "GAS/PCAbilitySystemComponent.h"
#include "GAS/Data/HitReactBoneConfig.h"

// Sets default values
APCBaseCharacter::APCBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

UAbilitySystemComponent* APCBaseCharacter::GetAbilitySystemComponent() const
{
	return ASC;
}

FVector APCBaseCharacter::GetSocketLocationByName_Implementation(FName SocketName)
{
	if (!GetMesh())
	{
		return FVector::ZeroVector;
	}

	if (!GetMesh()->DoesSocketExist(SocketName))
	{
		return FVector::ZeroVector;
	}

	return GetMesh()->GetSocketLocation(SocketName);
}

UDataTable* APCBaseCharacter::GetHitReactDataTable_Implementation()
{
	return HitReactTable;
}

void APCBaseCharacter::FillHitReactInfo_Implementation( FVector HitLocation, FName Bone, ECardinalDirection& HitDirection, EHitZone& HitZone)
{
	const FVector ToHit = (HitLocation - GetActorLocation()).GetSafeNormal();

	const FVector Forward = GetActorForwardVector();
	const FVector Right   = GetActorRightVector();
	
	const float ForwardDot = FVector::DotProduct(ToHit, Forward); 
	const float RightDot   = FVector::DotProduct(ToHit, Right);    

	if (FMath::Abs(ForwardDot) >= FMath::Abs(RightDot))
	{
		HitDirection= ForwardDot >= 0.f ? ECardinalDirection::Front : ECardinalDirection::Back;
	}
	else
	{
		HitDirection= RightDot >= 0.f ? ECardinalDirection::Right : ECardinalDirection::Left;
	}
	
	HitZone=BonesToZonesDataAsset->GetZoneForBone(Bone,GetMesh());

}


void APCBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APCBaseCharacter::InitializeAttributes()
{
	ApplyAttributeInitEffect(PrimaryAttributes,1);
	ApplyAttributeInitEffect(SecondaryAttributes,1);
	ApplyAttributeInitEffect(VitalAttributes,1);
}

void APCBaseCharacter::ApplyAttributeInitEffect(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(ASC);
	check(GameplayEffectClass);
	FGameplayEffectContextHandle Context=ASC->MakeEffectContext();
	Context.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpec=ASC->MakeOutgoingSpec(GameplayEffectClass,Level,Context);
	ASC->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data.Get());
}

void APCBaseCharacter::GrantStartUpAbilities(float Level=1) const
{
	if (ASC && !StartUpAbilities.IsEmpty()) 
		Cast<UPCAbilitySystemComponent>(ASC)->GiveStartUpAbilities(StartUpAbilities,Level);
}

void APCBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


