// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetControllers/PCBaseWidgetController.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeChangeSignature, float, NewValue);

UCLASS()
class PRIMORDIALCORES_API UOverlayWidgetController : public UPCBaseWidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallBackToDependencies() override;
	
	UPROPERTY(BlueprintAssignable, Category="PC|Delegate")
	FAttributeChangeSignature OnHealthChangeDelegate;
	
	UPROPERTY(BlueprintAssignable, Category="PC|Delegate")
	FAttributeChangeSignature OnMaxHealthChangeDelegate;
	
	UPROPERTY(BlueprintAssignable, Category="PC|Delegate")
	FAttributeChangeSignature OnManaChangeDelegate;
	
	UPROPERTY(BlueprintAssignable, Category="PC|Delegate")
	FAttributeChangeSignature OnMaxManaChangeDelegate;
	
};
