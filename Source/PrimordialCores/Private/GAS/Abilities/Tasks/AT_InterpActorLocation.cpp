// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/Tasks/AT_InterpActorLocation.h"

UAT_InterpActorLocation::UAT_InterpActorLocation()
{
	bTickingTask = true;
}

UAT_InterpActorLocation* UAT_InterpActorLocation::InterpToLocation(UGameplayAbility* OwningAbility,FVector TargetLocation, float Duration)
{
	UAT_InterpActorLocation* MyTask =
	   NewAbilityTask<UAT_InterpActorLocation>(OwningAbility);

	MyTask->TargetLocation = TargetLocation;
	MyTask->Duration = Duration;

	return MyTask;
}

void UAT_InterpActorLocation::Activate()
{
	if (AActor* AbilityActor = GetAvatarActor())
	{
		StartLocation = AbilityActor->GetActorLocation();
		TimeElapsed = 0.f;
	}
}

void UAT_InterpActorLocation::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (AActor* AbilityActor = GetAvatarActor())
	{
		TimeElapsed += DeltaTime;

		float Alpha = FMath::Clamp(TimeElapsed / Duration, 0.f, 1.f);
		
		FVector NewLocation = FMath::Lerp(StartLocation, TargetLocation, Alpha);

		AbilityActor->SetActorLocation(NewLocation);

		if (Alpha >= 1.f)
		{
			OnFinished.Broadcast();
			EndTask();
		}
	}
}