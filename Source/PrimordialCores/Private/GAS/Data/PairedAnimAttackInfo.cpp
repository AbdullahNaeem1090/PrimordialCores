// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Data/PairedAnimAttackInfo.h"

FPairedAnimInfo UPairedAnimAttackInfo::GetRandomPairAnimInfoForTag(FGameplayTag InTag) const
{
	TArray<const FPairedAnimInfo*> Matched;
    
	for (const FPairedAnimInfo& Info : PairedAnimInfoArray)
	{
		if (Info.InputTag == InTag)
			Matched.Add(&Info);
	}

	if (Matched.IsEmpty()) return FPairedAnimInfo();
    
	return *Matched[FMath::RandRange(0, Matched.Num() - 1)];
}
