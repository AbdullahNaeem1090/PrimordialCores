// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/PCBaseCharacter.h"
#include "PCEnemy.generated.h"

/**
 * 
 */
UCLASS()
class PRIMORDIALCORES_API APCEnemy : public APCBaseCharacter
{
	GENERATED_BODY()
	
public:
	APCEnemy();
	
	UPROPERTY(BlueprintReadOnly)
	float Health=0;
	
	//combat interface (just for )
	//combat interface for character only
	virtual UTargetLockComponent* GetLockTargetComponent_Implementation() override;
	virtual AActor* GetOpponentTarget_Implementation() override;
	virtual int32 GetCharacterLevel_Implementation() override;
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	float Level=1;
	
	
};
