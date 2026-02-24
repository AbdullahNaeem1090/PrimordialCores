// Fill out your copyright notice in the Description page of Project Settings.


#include "PCAssetManager.h"
#include "AbilitySystemGlobals.h"
#include "PCGameplayTags.h"

UPCAssetManager& UPCAssetManager::Get()
{
	check(GEngine);
	
	UPCAssetManager* AuraAssetManager = Cast<UPCAssetManager>(GEngine->AssetManager);
	return *AuraAssetManager;
}

void UPCAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FPCGameplayTags::InitializeNativeGameplayTags();
	UAbilitySystemGlobals::Get().InitGlobalData();
}