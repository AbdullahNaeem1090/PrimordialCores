// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PCCharacter.h"

#include "AbilitySystemComponent.h"
#include "Actors/Components/TargetLockComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/PCPlayerController.h"
#include "Player/PCPlayerState.h"
#include "UI/HUD/PCHUD.h"

APCCharacter::APCCharacter()
{
	SpringArmComp=CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraComp=CreateDefaultSubobject<UCameraComponent>("Character Camera");
	CameraComp->SetupAttachment(SpringArmComp);
	SpringArmComp->SetupAttachment(GetRootComponent());
	SphereComponent=CreateDefaultSubobject<USphereComponent>("LockSphere");
	SphereComponent->SetupAttachment(GetRootComponent());
	
	TargetLockComponent=CreateDefaultSubobject<UTargetLockComponent>("TargetLockComp");
	
}

void APCCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	InitializeSetUp();
	
}

UTargetLockComponent* APCCharacter::GetLockTargetComponent_Implementation()
{
	return TargetLockComponent;
}

AActor* APCCharacter::GetOpponentTarget_Implementation()
{
	if (TargetLockComponent && TargetLockComponent->IsLocked())
	{
		return TargetLockComponent->GetLockedTarget();
	}
	return nullptr;
}

int32 APCCharacter::GetCharacterLevel_Implementation()
{
	if (APCPlayerState* PS = GetPlayerState<APCPlayerState>())
	{
		return PS->Level;
	}
	return 1;
}


void APCCharacter::InitializeSetUp()
{
	
	APCPlayerState* PS = GetPlayerState<APCPlayerState>();
	check(PS);
	PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS,this);
	ASC=PS->GetAbilitySystemComponent();
	AS=PS->GetAttributeSet();
	
	if (APCPlayerController* PC = Cast<APCPlayerController>(GetController()))
	{
		if (APCHUD* AuraHUD = Cast<APCHUD>(PC->GetHUD()))
		{
			AuraHUD->InitHud(PC, PS, ASC, AS);
		}
	}
	
	InitializeAttributes();
	GrantStartUpAbilities(PS->Level);

}
