// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityFunctionLibrary.h"

float UUtilityFunctionLibrary::CalculateAttackUtility(float DistanceToPlayer, float DistanceToVIP, int32 ThreatLevel)
{
	return FMath::Clamp(DistanceToPlayer/10000.0f,0.0f,1.0f);
}

float UUtilityFunctionLibrary::CalculateHidingUtility(float DistanceToPlayer, float DistanceToVIP)
{
	return DistanceToPlayer;
}