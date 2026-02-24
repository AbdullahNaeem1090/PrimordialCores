// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PCEnemy.h"

#include "GAS/PCAbilitySystemComponent.h"
#include "GAS/PCAttributeSet.h"

APCEnemy::APCEnemy()
{
	ASC = CreateDefaultSubobject<UPCAbilitySystemComponent>("AbilitySystemComponent");
	AS = CreateDefaultSubobject<UPCAttributeSet>("AttributeSet");
}

UTargetLockComponent* APCEnemy::GetLockTargetComponent_Implementation()
{
	return nullptr;
}

AActor* APCEnemy::GetOpponentTarget_Implementation()
{
	return nullptr;
}

int32 APCEnemy::GetCharacterLevel_Implementation()
{
	return Level;
}

void APCEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	ASC->InitAbilityActorInfo(this,this);
	InitializeAttributes();
	GrantStartUpAbilities(Level);
	if (const UPCAttributeSet* PCAS = Cast<UPCAttributeSet>(AS))
	{
		ASC->GetGameplayAttributeValueChangeDelegate(PCAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				Health=Data.NewValue;
			}
		);
		
		Health=PCAS->GetHealth();
	}
}
