// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PCHUD.generated.h"

struct FWidgetControllerParams;
class UOverlayWidgetController;
class UPCBaseUserWidget;
class UAbilitySystemComponent;  
class UAttributeSet; 

UCLASS()
class PRIMORDIALCORES_API APCHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void InitHud(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
private:
	UPROPERTY(EditAnywhere ,Category="PC|Class To Set")
	TSubclassOf<UPCBaseUserWidget> OverlayWidgetClass;
	
	UPROPERTY(EditAnywhere,Category="PC|Class To Set")
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	
	UPROPERTY()
	TObjectPtr<UPCBaseUserWidget>  OverlayWidget;	
	
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
};
