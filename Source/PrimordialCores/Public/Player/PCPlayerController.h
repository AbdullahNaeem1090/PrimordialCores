// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "PCPlayerController.generated.h"

class UTargetLockComponent;
class APCBaseCharacter;
class UInputMappingContext;
class UInputAction;
class UPCAbilitySystemComponent;

UCLASS()
class PRIMORDIALCORES_API APCPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APCPlayerController();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	
	void Move(const FInputActionValue& Value)  ;
	void Look(const FInputActionValue& Value);
	void SpaceBarHandle(const FInputActionValue& Value);
	void LMBPressHandle(const FInputActionValue& Value);
	void LMBReleaseHandle(const FInputActionValue& Value);
	void RMBPressHandle(const FInputActionValue& Value);
	void RMBReleaseHandle(const FInputActionValue& Value);
	void ShiftHandle(const FInputActionValue& Value);
	void CtrlHandle(const FInputActionValue& Value);
	
	UTargetLockComponent* GetTargetLockComp();
	
	
	APCBaseCharacter* GetPCCharacter();
	UPCAbilitySystemComponent* GetPCAbilitySystem(); 
	
private:
	
	UPROPERTY(EditDefaultsOnly,Category="Input Actions")
	TObjectPtr<UInputMappingContext> MappingContext;
	
	UPROPERTY(EditDefaultsOnly,Category="Input Actions")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditDefaultsOnly,Category="Input Actions")
	TObjectPtr<UInputAction> LookAroundAction;
	
	UPROPERTY(EditDefaultsOnly,Category="Input Actions")
	TObjectPtr<UInputAction> SpaceBarAction;
	
	UPROPERTY(EditDefaultsOnly,Category="Input Actions")
	TObjectPtr<UInputAction> LMBAction;
	
	UPROPERTY(EditDefaultsOnly,Category="Input Actions")
	TObjectPtr<UInputAction> RMBAction;
	
	UPROPERTY(EditDefaultsOnly,Category="Input Actions")
	TObjectPtr<UInputAction> ShiftAction;
	
	UPROPERTY(EditDefaultsOnly,Category="Input Actions")
	TObjectPtr<UInputAction> CtrlAction;
	
	UPROPERTY()
	TObjectPtr<APCBaseCharacter> ControlledCharacter;
	
	UPROPERTY()
	TObjectPtr<UPCAbilitySystemComponent> ASC;
	
	UPROPERTY()
	TObjectPtr<UTargetLockComponent> TargetLockComponent;
	
	bool bCtrlPressed = false;
	bool bShiftPressed = false;
	
	void LookAtLockedTarget(float DeltaTime);

};
