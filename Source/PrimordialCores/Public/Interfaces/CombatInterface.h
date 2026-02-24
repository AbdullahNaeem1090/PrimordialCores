
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

enum class EHitZone : uint8;
enum class ECardinalDirection : uint8;
class UTargetLockComponent;

UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PRIMORDIALCORES_API ICombatInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	FVector GetSocketLocationByName(FName SocketName);
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	UTargetLockComponent* GetLockTargetComponent();
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
    AActor* GetOpponentTarget();
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	UDataTable* GetHitReactDataTable();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void FillHitReactInfo(
		FVector HitLocation,
		FName Bone,
		UPARAM(ref) ECardinalDirection& HitDirection,
		UPARAM(ref) EHitZone& HitZone
	);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	int32 GetCharacterLevel();
};
