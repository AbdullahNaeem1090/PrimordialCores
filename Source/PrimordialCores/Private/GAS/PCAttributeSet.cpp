// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/PCAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "PCGameplayTags.h"
#include "GameFramework/Character.h"
#include "GAS/Effects/PCEffectContext.h"
#include "Interfaces/CombatInterface.h"


void UPCAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
	
}

void UPCAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	FEffectProperties Props;
	SetEffectProperties(Data, Props);
	
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float Damage = GetIncomingDamage();

		const float NewHealth = GetHealth() - Damage;
		
		
		if (NewHealth <= 0.f)
		{
			FGameplayTagContainer CancelTagContainer;
			CancelTagContainer.AddTag(FPCGameplayTags::Get().Ability_Combat_Physical_Kick_Combo);
			CancelTagContainer.AddTag(FPCGameplayTags::Get().Ability_Combat_Physical_Punch_Combo);
			FPCEffectContext* EffectContext=StaticCast<FPCEffectContext*>(Props.EffectContextHandle.Get());
			FVector HitLocation=EffectContext->GetHitResult()->ImpactPoint;
			FGameplayTag HitType=EffectContext->GetHitType();
		    ICombatInterface::Execute_Death(Props.TargetAvatarActor,HitLocation,HitType);
			Props.SourceASC->CancelAbilities(&CancelTagContainer);
			
		}
		else
		{
			SendHitReactEvent(Props);
		}

		SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));

		SetIncomingDamage(0.f);  

	}
	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
}

void UPCAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}

void UPCAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	Props.EffectContextHandle=Data.EffectSpec.GetContext();
	Props.SourceASC=Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	if (
		IsValid(Props.SourceASC) && 
		Props.SourceASC->AbilityActorInfo.IsValid() && 
		Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid()
		)
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
	
}

void UPCAttributeSet::SendHitReactEvent(FEffectProperties& Props)
{
	FGameplayEventData Payload;
	Payload.EventTag = FPCGameplayTags::Get().Event_HitReact;
	Payload.ContextHandle=Props.EffectContextHandle;
	Payload.Target=Props.TargetAvatarActor;
	Payload.Instigator=Props.SourceAvatarActor;
	
	Props.TargetASC->HandleGameplayEvent(
		FPCGameplayTags::Get().Event_HitReact,
		&Payload
	);
}
