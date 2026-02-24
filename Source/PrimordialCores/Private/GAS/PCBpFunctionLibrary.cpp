// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/PCBpFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "PCGameplayTags.h"
#include "GAS/Data/HitReactBoneConfig.h"
#include "GAS/Effects/PCEffectContext.h"


void UPCBpFunctionLibrary::ApplyDamageEffectToTarget(
	TSubclassOf<UGameplayEffect> EffectClass,
	AActor* SourceActor,
	UAbilitySystemComponent* TargetAsc,
	FGameplayTag InHitType,
	const FHitResult& HitResult,
	float BaseDamage,
	float Level)
{
	if (!EffectClass || !SourceActor || !TargetAsc) return;

	UAbilitySystemComponent* SourceAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SourceActor);
	if (!SourceAsc) return;

	FGameplayEffectContextHandle ContextHandle = SourceAsc->MakeEffectContext();
    
	FPCEffectContext* PCContext = static_cast<FPCEffectContext*>(ContextHandle.Get());
	PCContext->SetHitType(InHitType);	
	PCContext->AddHitResult(HitResult, true);
	PCContext->AddInstigator(SourceActor, SourceActor);

	FGameplayEffectSpecHandle SpecHandle = SourceAsc->MakeOutgoingSpec(EffectClass, Level, ContextHandle);
	if (!SpecHandle.IsValid()) return;

	SpecHandle.Data->SetSetByCallerMagnitude(FPCGameplayTags::Get().Damage_Data,BaseDamage);
	TargetAsc->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	
}

bool UPCBpFunctionLibrary::GetHitResultFromEffectContext(const FGameplayEffectContextHandle& Handle, FHitResult& OutHitResult,FGameplayTag& OutHitType)
{
	if (!Handle.IsValid()) return false;
    
	FPCEffectContext* PCContext = static_cast<FPCEffectContext*>(
		const_cast<FGameplayEffectContext*>(Handle.Get())
	);
	if (!PCContext) return false;
    
	const FHitResult* HitResult = PCContext->GetHitResult();
	const FGameplayTag HitType = PCContext->GetHitType();
	
	if (!HitResult) return false;
    
	OutHitResult = *HitResult;
	OutHitType = HitType;
	return true;
}

UAnimMontage* UPCBpFunctionLibrary::GetHitReactAnimMontageFromTable(FGameplayTag AttackType,
	ECardinalDirection HitDirection, EHitZone HitZone,const UDataTable* HitReactTable)
{
	if (!HitReactTable) return nullptr;

	TArray<FPCHitReactRow*> AllRows;
	HitReactTable->GetAllRows<FPCHitReactRow>(TEXT("GetHitReactAnimMontageFromTable"), AllRows);
	if (AllRows.IsEmpty()) return nullptr;

	for (FPCHitReactRow* Row : AllRows)
	{
		if (Row->HitType      == AttackType  &&
			Row->HitZone      == HitZone     &&
			Row->HitDirection == HitDirection)
		{
			return Row->HitReactMontage;
		}
	}

	for (FPCHitReactRow* Row : AllRows)
	{
		if (Row->HitType == AttackType && Row->HitZone == HitZone)
		{
			return Row->HitReactMontage;
		}
	}

	for (FPCHitReactRow* Row : AllRows)
	{
		if (Row->HitType == AttackType && Row->HitZone == EHitZone::Default)
		{
			return Row->HitReactMontage;
		}
	}

	return nullptr;
}
