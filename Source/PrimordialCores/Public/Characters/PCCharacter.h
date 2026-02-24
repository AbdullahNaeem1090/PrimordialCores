// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/PCBaseCharacter.h"
#include "PCCharacter.generated.h"


class UTargetLockComponent;
class USphereComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class PRIMORDIALCORES_API APCCharacter : public APCBaseCharacter
{
	GENERATED_BODY()
	
public:
	APCCharacter();
	virtual void PossessedBy(AController* NewController) override;
	
	//combat interface for character only
	virtual UTargetLockComponent* GetLockTargetComponent_Implementation() override;
	virtual AActor* GetOpponentTarget_Implementation() override;
	virtual int32 GetCharacterLevel_Implementation() override;

	
private:
	
	void InitializeSetUp();
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> SpringArmComp;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USphereComponent> SphereComponent;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTargetLockComponent> TargetLockComponent;
};
