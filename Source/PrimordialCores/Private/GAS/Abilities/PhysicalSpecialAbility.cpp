// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/PhysicalSpecialAbility.h"

bool UPhysicalSpecialAbility::GetAndSetPairedAnimInfo()
{
    if (!PairedAnimInfoAsset) return false;
    
    PairAnimInfo = PairedAnimInfoAsset->GetRandomPairAnimInfoForTag(InputTag);
    return PairAnimInfo.AttackAnim != nullptr;
}

bool UPhysicalSpecialAbility::IsTargetInIdealRange() const 
{
	if (!Target || !PairedAnimInfoAsset || !Attacker)
		return false;
	
	const FVector AttackerLocation = Attacker->GetActorLocation();
	const FVector TargetLocation = Target->GetActorLocation();

	const float Distance = FVector::Dist(AttackerLocation, TargetLocation);
	const float LowerBound = PairAnimInfo.IdealDistance - PairAnimInfo.DistanceTolerance;
	const float UpperBound = PairAnimInfo.IdealDistance + PairAnimInfo.DistanceTolerance;

	return Distance >= LowerBound && Distance <= UpperBound;
}


    bool UPhysicalSpecialAbility::TargetIsFacingAttackerInRange(float MinAngle, float MaxAngle) const
    {
    	if (!Target||!Attacker) return false;
    	
    	const FVector TargetForward = Target->GetActorForwardVector();
    	const FVector ToAttacker = (Attacker->GetActorLocation() - Target->GetActorLocation()).GetSafeNormal();
    
    	const float Angle = FMath::RadiansToDegrees(
    		FMath::Atan2(
    			FVector::DotProduct(FVector::CrossProduct(TargetForward, ToAttacker), FVector::UpVector),
    			FVector::DotProduct(TargetForward, ToAttacker)
    		)
    	);
    
    	return Angle >= MinAngle && Angle <= MaxAngle;
    }

