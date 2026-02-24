// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Data/HitReactBoneConfig.h"

EHitZone UHitReactBoneConfig::GetZoneForBone(FName BoneName, USkeletalMeshComponent* Mesh) const
{
	if (!Mesh || BoneName == NAME_None) return DefaultZone;

	FName Current = BoneName;

	while (Current != NAME_None)
	{
		if (const EHitZone* Zone = BoneToZoneMap.Find(Current))
		{
			return *Zone;
		}
		Current = Mesh->GetParentBone(Current);
	}

	return DefaultZone;
}
