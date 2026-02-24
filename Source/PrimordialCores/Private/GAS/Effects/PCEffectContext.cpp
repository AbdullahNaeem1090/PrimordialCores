#include "GAS/Effects/PCEffectContext.h"

bool FPCEffectContext::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	bOutSuccess = true;

	// Serialize parent
	bool bSuperSuccess = true;
	Super::NetSerialize(Ar, Map, bSuperSuccess);
	bOutSuccess &= bSuperSuccess;

	// Serialize HitType
	bool bHitTypeSuccess = true;
	HitType.NetSerialize(Ar, Map, bHitTypeSuccess);
	bOutSuccess &= bHitTypeSuccess;

	return true;
}