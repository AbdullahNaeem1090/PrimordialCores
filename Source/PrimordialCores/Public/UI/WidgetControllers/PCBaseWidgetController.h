// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PCBaseWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class APCPlayerController;
class APCPlayerState;
class UPCAbilitySystemComponent;
class UPCAttributeSet;


struct FWidgetControllerParams
{

	FWidgetControllerParams() {}
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
	: PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS) {}

	TObjectPtr<APlayerController> PlayerController = nullptr;

	TObjectPtr<APlayerState> PlayerState = nullptr;

	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};

UCLASS(BlueprintType, Blueprintable)
class PRIMORDIALCORES_API UPCBaseWidgetController : public UObject
{
	GENERATED_BODY()
	
public:
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);
	
protected:
	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues();
	
	virtual void BindCallBackToDependencies(); 
	
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;
	
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APCPlayerController> PCPlayerController;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APCPlayerState> PCPlayerState;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UPCAbilitySystemComponent> PCAbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UPCAttributeSet> PCAttributeSet;
	
	APCPlayerController* GetPCPC();
	APCPlayerState* GetPCPS();
	UPCAbilitySystemComponent* GetPCASC();
	UPCAttributeSet* GetPCAS();
};
