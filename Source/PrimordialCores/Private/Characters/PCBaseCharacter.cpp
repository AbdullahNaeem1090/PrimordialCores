// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PCBaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/PCAbilitySystemComponent.h"
#include "GAS/Data/HitReactBoneConfig.h"
#include "GAS/PCBpFunctionLibrary.h"


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

void APCBaseCharacter::Death_Implementation(FVector HitLocation, FGameplayTag HitType)
{
	ECardinalDirection HitDirection=UPCBpFunctionLibrary::GetCardinalDirection(this,HitLocation);
	UAnimMontage* DeathMontage=UPCBpFunctionLibrary::GetDeathMontageFromTable(HitType,HitDirection,DeathMontageTable);
	
	if (!DeathMontage) return;
	
	float Duration = PlayAnimMontage(DeathMontage);

	if (Duration > 0.f)
	{
		FOnMontageBlendingOutStarted BlendDelegate;
		BlendDelegate.BindUObject(this, &APCBaseCharacter::OnDeathMontageBlendingOut);

		GetMesh()->GetAnimInstance()->Montage_SetBlendingOutDelegate(BlendDelegate, DeathMontage);
	}
}
void APCBaseCharacter::OnDeathMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted)
{
	if (bInterrupted) return;

	// 1. Stop all movement cleanly
	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->DisableMovement();

	// 2. Disable capsule collision
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 3. Detach mesh from capsule (VERY IMPORTANT)
	GetMesh()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	// 4. Optional: freeze animation pose
	GetMesh()->bPauseAnims = true;

	// 5. Enable ragdoll
	GetMesh()->SetCollisionProfileName("Ragdoll");
	GetMesh()->SetSimulatePhysics(true);
}

void APCBaseCharacter::FillHitReactInfo_Implementation( FVector HitLocation, FName Bone, ECardinalDirection& HitDirection, EHitZone& HitZone)
{
	HitDirection=UPCBpFunctionLibrary::GetCardinalDirection(this,HitLocation);
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


