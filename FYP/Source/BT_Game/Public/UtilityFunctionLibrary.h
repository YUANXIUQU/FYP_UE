// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UtilityFunctionLibrary.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EAction : uint8
{
	Attack, // Engage the player
	Hiding, // Take cover
	Retreating,  // Run away
	Chasing,  // Follow the player
	BlockingExit, // Block the exit
	RandomSearching // Search
};

USTRUCT(BlueprintType)
struct FActionScore
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite)
	EAction Action; // The action type

	UPROPERTY(BlueprintReadWrite)
	float Score; // Utility score for this action

};

UCLASS()
class BT_GAME_API UUtilityFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "Utility")
	static float EvaluateConsideration(float NormalizedValue, UCurveFloat* Curve);

	//Attack Mode
	UFUNCTION(BlueprintPure, Category = "AI|Utility")
	static float CalculateAttackUtility(float DistanceToPlayer, float Health, float seePlayer, UCurveFloat* DistanceCurve);

	//Hideing
	UFUNCTION(BlueprintPure, Category = "AI|Utility")
	static float CalculateHidingUtility(float DistanceToPlayer, float Health, float TimeSinceLastDamage);

	//Retreating
	UFUNCTION(BlueprintPure, Category = "AI|Utility")
	static float CalculateRetreatUtility(float DistanceToPlayer, float Health, float seePlayer);

	//Chasing
	UFUNCTION(BlueprintPure, Category = "AI|Utility")
	static float CalculateChasingUtility(float Health, float seePlayer,float TimeSinceSeenPlayer);

	//BlockingExit
	UFUNCTION(BlueprintPure, Category = "AI|Utility")
	static float CalculateBlockingExitUtility(float DistanceToExit, float PlayerDistanceToExit);

	//RandomSearch
	UFUNCTION(BlueprintPure, Category = "AI|Utility")
	static float CalculateRandomSearchUtility(float seePlayer,float TimeSinceSeenPlayer, float Health);

	//Selecting Best Action
	UFUNCTION(BlueprintPure, Category = "AI|UtilitySelector")
	static EAction SelectAction(const TArray<FActionScore>& score, EAction currenAction);


};
