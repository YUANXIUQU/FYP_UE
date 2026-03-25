// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UtilityFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class BT_GAME_API UUtilityFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "AI|Utility")
	static float CalculateAttackUtility(float DistanceToPlayer,float DistanceToVIP, int32 ThreatLevel);
	UFUNCTION(BlueprintPure, Category = "AI|Utility")
	static float CalculateHidingUtility(float DistanceToPlayer, float DistanceToVIP);
	
};
