#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "PCStructs.generated.h"

USTRUCT(BlueprintType)
struct FPhysicalAttackData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName AttackName = FName();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttackType = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ComboSlot = FName();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName NextComboSlot = FName();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float BaseDamage = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName SocketName = FName();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DistanceRange =0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* AttackerMontage = nullptr;


#if WITH_EDITOR
	virtual void OnDataTableChanged(const UDataTable* InDataTable, const FName InRowName) override
	{
		Super::OnDataTableChanged(InDataTable, InRowName);
		AttackName = InRowName;
	}
#endif
};
