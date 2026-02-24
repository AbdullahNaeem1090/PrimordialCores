// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetControllers/OverlayWidgetController.h"
#include "GAS/PCAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	OnHealthChangeDelegate.Broadcast(GetPCAS()->GetHealth());
	OnMaxHealthChangeDelegate.Broadcast(GetPCAS()->GetMaxHealth());
	OnManaChangeDelegate.Broadcast(GetPCAS()->GetMana());
	OnMaxManaChangeDelegate.Broadcast(GetPCAS()->GetMaxMana());
}

void UOverlayWidgetController::BindCallBackToDependencies()
{	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetPCAS()->GetHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{
		OnHealthChangeDelegate.Broadcast(Data.NewValue);
	});
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetPCAS()->GetMaxHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{
		OnMaxHealthChangeDelegate.Broadcast(Data.NewValue);
	});
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetPCAS()->GetManaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{
		OnManaChangeDelegate.Broadcast(Data.NewValue);
	});
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetPCAS()->GetMaxManaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{
		OnMaxManaChangeDelegate.Broadcast(Data.NewValue);
	});
}
