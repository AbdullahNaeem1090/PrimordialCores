// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/PCBpFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "PCGameplayTags.h"
#include "GAS/Data/HitReactBoneConfig.h"
#include "GAS/Effects/PCEffectContext.h"
#include "PrimordialCores/PCStructs.h"


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

UAnimMontage* UPCBpFunctionLibrary::GetDeathMontageFromTable(FGameplayTag HitType, ECardinalDirection HitDirection,
	const UDataTable* DeathMontageTable)
{
	if (!DeathMontageTable) return nullptr;
	TArray<FPCDeathRow*> AllRows;
	
	DeathMontageTable->GetAllRows<FPCDeathRow>(TEXT("GetDeathMontageFromTable"), AllRows);
	if (AllRows.IsEmpty()) return nullptr;

	for (FPCDeathRow* Row : AllRows)
	{
		if (Row->HitType      == HitType  &&
			Row->HitDirection == HitDirection)
		{
			return Row->DeathMontage;
		}
	}
	
	for (FPCDeathRow* Row : AllRows)
	{
		if (Row->HitDirection == HitDirection)
		{
			return Row->DeathMontage;
		}
	}
	
	return nullptr;
	
}


FPhysicalAttackData UPCBpFunctionLibrary::GetRandomAttackInfo(
    const UDataTable* AttackDataTable,
    const FGameplayTagContainer& AttackTypes,
    bool& bFound)
{
    bFound = false;
    check(AttackDataTable);

    if (AttackTypes.IsEmpty()) return FPhysicalAttackData();

    TArray<FPhysicalAttackData*> AllRows;
    AttackDataTable->GetAllRows(TEXT(""), AllRows);

    TArray<FPhysicalAttackData*> MatchingRows;
    for (FPhysicalAttackData* Row : AllRows)
    {
        if (Row && Row->AttackType.MatchesAny(AttackTypes))
        {
            MatchingRows.Add(Row);
        }
    }

    if (MatchingRows.IsEmpty()) return FPhysicalAttackData();

    const int32 Index = FMath::RandRange(0, MatchingRows.Num() - 1);
    bFound = true;
    return *MatchingRows[Index];
}

FPhysicalAttackData UPCBpFunctionLibrary::GetAttackInfoBySlot(
    const UDataTable* AttackDataTable,
    FName Slot,
    bool& bFound)
{
    bFound = false;
    check(AttackDataTable);

    TArray<FPhysicalAttackData*> AllRows;
    AttackDataTable->GetAllRows(TEXT(""), AllRows);

    for (FPhysicalAttackData* Row : AllRows)
    {
        if (Row && Row->ComboSlot == Slot)
        {
            bFound = true;
            return *Row;
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("GetAttackInfoBySlot: No attack found for slot '%s'"), *Slot.ToString());
    return FPhysicalAttackData();
}

FPhysicalAttackData UPCBpFunctionLibrary::GetAttackInfoByName(
    const UDataTable* AttackDataTable,
    FName Name,
    bool& bFound)
{
    bFound = false;
    check(AttackDataTable);

    // Fast path — row key lookup
    FPhysicalAttackData* Row = AttackDataTable->FindRow<FPhysicalAttackData>(Name, TEXT(""));
    if (Row)
    {
        bFound = true;
        return *Row;
    }

    // Fallback — manual search by AttackName field
    TArray<FPhysicalAttackData*> AllRows;
    AttackDataTable->GetAllRows(TEXT(""), AllRows);

    for (FPhysicalAttackData* R : AllRows)
    {
        if (R && R->AttackName == Name)
        {
            bFound = true;
            return *R;
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("GetAttackInfoByName: No attack found with name '%s'"), *Name.ToString());
    return FPhysicalAttackData();
}

ECardinalDirection UPCBpFunctionLibrary::GetCardinalDirection(AActor* Actor,FVector Location)
{
	if (Actor==nullptr) return ECardinalDirection::Front;
	
	const FVector ToHit = (Location - Actor->GetActorLocation()).GetSafeNormal();
	
	const float ForwardDot = FVector::DotProduct(ToHit, Actor->GetActorForwardVector()); 
	const float RightDot   = FVector::DotProduct(ToHit, Actor->GetActorRightVector());    

	if (FMath::Abs(ForwardDot) >= FMath::Abs(RightDot))
	{
		return  ForwardDot >= 0.f ? ECardinalDirection::Front : ECardinalDirection::Back;
	}
	else
	{
		return  RightDot >= 0.f ? ECardinalDirection::Right : ECardinalDirection::Left;
	}
}
