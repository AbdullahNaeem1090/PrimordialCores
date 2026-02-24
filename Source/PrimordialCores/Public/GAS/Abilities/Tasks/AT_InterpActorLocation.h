// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AT_InterpActorLocation.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMoveTaskDelegate);

UCLASS()
class PRIMORDIALCORES_API UAT_InterpActorLocation : public UAbilityTask
{
	GENERATED_BODY()
public:
	
	UAT_InterpActorLocation();
	
	UPROPERTY(BlueprintAssignable)
	FMoveTaskDelegate OnFinished;
	
	UFUNCTION(BlueprintCallable, meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility"))
	static UAT_InterpActorLocation* InterpToLocation(
		UGameplayAbility* OwningAbility,
		FVector TargetLocation,
		float Duration
		);
	
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
	
private:
	FVector StartLocation;
	FVector TargetLocation;
	float Duration;
	float TimeElapsed;

};
