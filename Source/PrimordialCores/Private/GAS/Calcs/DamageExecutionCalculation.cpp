// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Calcs/DamageExecutionCalculation.h"

#include "PCGameplayTags.h"
#include "GAS/PCAttributeSet.h"
#include "Interfaces/CombatInterface.h"


struct PCDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResilience);
	
	PCDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPCAttributeSet,Armor,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPCAttributeSet,ArmorPenetration,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPCAttributeSet,CriticalHitChance,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPCAttributeSet,CriticalHitDamage,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPCAttributeSet,CriticalHitResilience,Target,false);
	}
};

static const PCDamageStatics& DamageStatics()
{
static PCDamageStatics Statics;
	return Statics;
}

UDamageExecutionCalculation::UDamageExecutionCalculation()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResilienceDef);
}

void UDamageExecutionCalculation::Execute_Implementation(
    const FGameplayEffectCustomExecutionParameters& ExecutionParams,
    FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
    const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

    const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

    FAggregatorEvaluateParameters EvaluationParameters;
    EvaluationParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    EvaluationParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    // =========================
    // Getting Base Damage
    // =========================

    float Damage = Spec.GetSetByCallerMagnitude(
    FPCGameplayTags::Get().Damage_Data,
    false,
    0.f
);

    if (Damage <= 0.f)
    {
        return;
    }

    // =========================
    // Capturing Attributes
    // =========================

    float TargetArmor = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
        DamageStatics().ArmorDef,
        EvaluationParameters,
        TargetArmor
    );
    TargetArmor = FMath::Max(TargetArmor, 0.f);

    float SourceArmorPenetration = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
        DamageStatics().ArmorPenetrationDef,
        EvaluationParameters,
        SourceArmorPenetration
    );
    SourceArmorPenetration = FMath::Clamp(SourceArmorPenetration, 0.f, 100.f);

    float SourceCritHitChance = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
        DamageStatics().CriticalHitChanceDef,
        EvaluationParameters,
        SourceCritHitChance
    );
    SourceCritHitChance = FMath::Clamp(SourceCritHitChance, 0.f, 100.f);

    float SourceCritDamage = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
        DamageStatics().CriticalHitDamageDef,
        EvaluationParameters,
        SourceCritDamage
    );
    SourceCritDamage = FMath::Max(SourceCritDamage, 0.f);

    float TargetCritResilience = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
        DamageStatics().CriticalHitResilienceDef,
        EvaluationParameters,
        TargetCritResilience
    );
    TargetCritResilience = FMath::Clamp(TargetCritResilience, 0.f, 100.f);

    // =========================
    // Armor Mitigation
    // =========================

    const float EffectiveArmor =
        TargetArmor * (1.f - SourceArmorPenetration / 100.f);

    Damage *= (100.f - EffectiveArmor) / 100.f;

    // =========================
    // Critical Hit
    // =========================

    const float EffectiveCritChance =
        FMath::Max(SourceCritHitChance - TargetCritResilience, 0.f);

    const bool bCritical =
        FMath::RandRange(1.f, 100.f) <= EffectiveCritChance;

    if (bCritical)
    {
        Damage = Damage * 2.f + SourceCritDamage;
    }

    // =========================
    // Output Damage
    // =========================

    OutExecutionOutput.AddOutputModifier(
        FGameplayModifierEvaluatedData(
            UPCAttributeSet::GetIncomingDamageAttribute(),
            EGameplayModOp::Additive,
            Damage
        )
    );
}
