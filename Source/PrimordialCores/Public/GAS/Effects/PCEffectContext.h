#pragma once
#include "GameplayEffectTypes.h"
#include "GameplayTagContainer.h"
#include "PCEffectContext.generated.h"

USTRUCT(BlueprintType)
struct FPCEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:

	// ── Overrides ────────────────────────────────────────────────

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FPCEffectContext::StaticStruct();
	}

	virtual FPCEffectContext* Duplicate() const override
	{
		FPCEffectContext* NewContext = new FPCEffectContext();
		*NewContext = *this;          
		if (GetHitResult())
		{
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

	virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;

	// ── Accessors ────────────────────────────────────────────────

	FGameplayTag GetHitType() const { return HitType; }
	void SetHitType(FGameplayTag InHitType) { HitType = InHitType; }

protected:

	UPROPERTY()   
	FGameplayTag HitType;
};


template<>
struct TStructOpsTypeTraits<FPCEffectContext>
	: public TStructOpsTypeTraitsBase2<FPCEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy          = true    
	};
};