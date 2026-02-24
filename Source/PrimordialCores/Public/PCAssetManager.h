// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "PCAssetManager.generated.h"


UCLASS()
class PRIMORDIALCORES_API UPCAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static UPCAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
