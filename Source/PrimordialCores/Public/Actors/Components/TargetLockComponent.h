// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetLockComponent.generated.h"


class USphereComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRIMORDIALCORES_API UTargetLockComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTargetLockComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ToggleLock(bool bEnable);
	
	bool IsTargetLockingEnabled() const { return bTargetLockingEnabled; }
	
	UFUNCTION(BlueprintPure)
	AActor* GetLockedTarget() const { return LockedTarget.Get(); }

	bool IsLocked() const { return bIsLocked; }
	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void TargetBeginOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);
	
	UFUNCTION()
	void TargetEndOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex);

private:
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* SphereComponent;
	
	UPROPERTY()
	TArray<TWeakObjectPtr<AActor>> Targets;
	
    UPROPERTY(EditDefaultsOnly)
	FName TargetTag="Enemy";
	
	UPROPERTY()
	TWeakObjectPtr<AActor> LockedTarget;
	
	bool bIsLocked = false;
	
	UPROPERTY(EditDefaultsOnly)
	bool bTargetLockingEnabled=false; 
	

};
