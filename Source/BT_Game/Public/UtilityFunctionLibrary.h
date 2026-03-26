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

	//Attack Mode
	UFUNCTION(BlueprintPure, Category = "AI|Utility")
	static float CalculateAttackUtility(float DistanceToPlayer, float Health, float seePlayer);

	UFUNCTION(BlueprintPure, Category = "AI|Utility")
	static float CalculateHidingUtility(float DistanceToPlayer, float Health,float seePlayer);

	UFUNCTION(BlueprintPure, Category = "AI|Utility")
	static float CalculateRetreatUtility(float DistanceToPlayer, float Health, float seePlayer);

	UFUNCTION(BlueprintPure, Category = "AI|Utility")
	static float CalculateChasingUtility(float DistanceToPlayer, float seePlayer,float );

	UFUNCTION(BlueprintPure, Category = "AI|Utility")
	static float CalculateBlockingExitUtility(float DistanceToPlayer, float DistanceToVIP);

	UFUNCTION(BlueprintPure, Category = "AI|Utility")
	static float CalculateFollowingVIPUtility(float DistanceToPlayer, float DistanceToVIP);

	UFUNCTION(BlueprintPure, Category = "AI|Utility")
	static float CalculateRandomSearchUtility(float DistanceToPlayer, float DistanceToVIP);


};
