// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Components/TargetLockComponent.h"
#include "Components/SphereComponent.h"

UTargetLockComponent::UTargetLockComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetComponentTickInterval(0.5f);
}

void UTargetLockComponent::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComponent = GetOwner()->FindComponentByClass<USphereComponent>();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&UTargetLockComponent::TargetBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this,&UTargetLockComponent::TargetEndOverlap);
}



void UTargetLockComponent::TargetBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || !OtherActor->ActorHasTag(TargetTag)) return ;
	Targets.AddUnique(OtherActor);
	
}

void UTargetLockComponent::TargetEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor || !OtherActor->ActorHasTag(TargetTag)) return ;
	
	Targets.Remove(OtherActor);
	if (LockedTarget.IsValid() && LockedTarget.Get()==OtherActor)
	{
		bIsLocked = false;
		LockedTarget=nullptr;
	}
}


void UTargetLockComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (!bTargetLockingEnabled) return;
	if (IsLocked() && LockedTarget.IsValid()) return;
	if (Targets.Num() == 0) return;

	float Distance = FLT_MAX;
	TWeakObjectPtr<AActor> TempTarget = nullptr;

	const FVector OwnerLoc = GetOwner()->GetActorLocation();

	for (int32 i = Targets.Num() - 1; i >= 0; i--)
	{
		if (!Targets[i].IsValid())
		{
			Targets.RemoveAt(i);
			continue;
		}

		float Dist = FVector::DistSquared(OwnerLoc,Targets[i]->GetActorLocation());

		if (Dist < Distance)
		{
			Distance = Dist;
			TempTarget = Targets[i];
		}
	}

	if (TempTarget.IsValid())
	{
		LockedTarget = TempTarget;
		bIsLocked = true;
	}
}

void UTargetLockComponent::ToggleLock(bool bEnable)
{
	bTargetLockingEnabled=bEnable;
}

