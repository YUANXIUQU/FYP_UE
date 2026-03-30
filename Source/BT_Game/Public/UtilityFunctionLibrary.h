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
	Attack,
	Hiding,
	Retreating,
	Chasing,
	BlockingExit,
	RandomSearching
};

USTRUCT(BlueprintType)
struct FActionScore
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite)
	EAction Action;

	UPROPERTY(BlueprintReadWrite)
	float Score;

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

	UFUNCTION(BlueprintPure, Category = "AI|Utility")
	static float CalculateHidingUtility(float DistanceToPlayer, float Health,float seePlayer);

	UFUNCTION(BlueprintPure, Category = "AI|Utility")
	static float CalculateRetreatUtility(float DistanceToPlayer, float Health, float seePlayer);

	UFUNCTION(BlueprintPure, Category = "AI|Utility")
	static float CalculateChasingUtility(float Health, float seePlayer,float TimeSinceSeenPlayer);

	UFUNCTION(BlueprintPure, Category = "AI|Utility")
	static float CalculateBlockingExitUtility(float DistanceToExit, float PlayerDistanceToExit);

	UFUNCTION(BlueprintPure, Category = "AI|Utility")
	static float CalculateFollowingVIPUtility(float DistanceToPlayer, float DistanceToVIP);

	UFUNCTION(BlueprintPure, Category = "AI|Utility")
	static float CalculateRandomSearchUtility(float seePlayer,float TimeSinceSeenPlayer);

	UFUNCTION(BlueprintPure, Category = "AI|UtilitySelector")
	static EAction SelectAction(const TArray<FActionScore>& score);


};
