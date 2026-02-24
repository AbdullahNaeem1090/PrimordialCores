// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetControllers/PCBaseWidgetController.h"

#include "GAS/PCAbilitySystemComponent.h"
#include "GAS/PCAttributeSet.h"
#include "Player/PCPlayerController.h"
#include "Player/PCPlayerState.h"

void UPCBaseWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UPCBaseWidgetController::BroadcastInitialValues()
{
}

void UPCBaseWidgetController::BindCallBackToDependencies()
{
}


APCPlayerController* UPCBaseWidgetController::GetPCPC()
{
	if (PCPlayerController == nullptr)
	{
		PCPlayerController = Cast<APCPlayerController>(PlayerController);
	}
	return PCPlayerController;
}

APCPlayerState* UPCBaseWidgetController::GetPCPS()
{
	if (PCPlayerState == nullptr)
	{
		PCPlayerState = Cast<APCPlayerState>(PlayerState);
	}
	return PCPlayerState;
}

UPCAbilitySystemComponent* UPCBaseWidgetController::GetPCASC()
{
	if (PCAbilitySystemComponent == nullptr)
	{
		PCAbilitySystemComponent = Cast<UPCAbilitySystemComponent>(AbilitySystemComponent);
	}
	return PCAbilitySystemComponent;
}

UPCAttributeSet* UPCBaseWidgetController::GetPCAS()
{
	if (PCAttributeSet == nullptr)
	{
		PCAttributeSet = Cast<UPCAttributeSet>(AttributeSet);
	}
	return PCAttributeSet;
}