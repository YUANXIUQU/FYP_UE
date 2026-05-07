// Fill out your copyright notice in the Description page of Project Settings.

#include "UtilityFunctionLibrary.h"

// Evaluate a normalized value using a curve (or just clamp if no curve)
float UUtilityFunctionLibrary::EvaluateConsideration(float NormalizedValue, UCurveFloat* Curve)
{
	if (!Curve)
	{
		// No curve provided, just clamp between 0 and 1
		return FMath::Clamp(NormalizedValue, 0.0f, 1.0f);
	}

	// Evaluate the curve and clamp the result
	return FMath::Clamp(Curve->GetFloatValue(NormalizedValue), 0.0f, 1.0f);
}

// Calculate utility for attacking the player
float UUtilityFunctionLibrary::CalculateAttackUtility(float DistanceToPlayer, float Health, float seePlayer, UCurveFloat* DistanceCurve)
{
	float NormalizedDistance = FMath::Clamp(DistanceToPlayer / 10000.0f, 0.0f, 1.0f);
	float HealthScore = FMath::Clamp(Health, 0.0f, 1.0f);
	float SeeScore = FMath::Clamp(seePlayer, 0.0f, 1.0f);

	// Get distance score using curve if provided
	float DistanceScore = EvaluateConsideration(NormalizedDistance, DistanceCurve);

	// If enemy can't see player, attack score is zero
	if (seePlayer <= 0.0f)
	{
		return 0.0f;
	}

	// Combine scores with weights
	float Score = DistanceScore * 0.6f + HealthScore * 0.2f + SeeScore * 0.2f;

	return FMath::Clamp(Score, 0.0f, 1.0f);
}

// Calculate utility for hiding
float UUtilityFunctionLibrary::CalculateHidingUtility(float DistanceToPlayer, float Health, float TimeSinceLastDamage)
{
	float DistanceScore = 1.0f - FMath::Clamp(DistanceToPlayer / 10000.0f, 0.0f, 1.0f);
	float HealthScore = 1.0f - FMath::Clamp(Health, 0.0f, 1.0f);
	float RecentDamageScore = 1 - FMath::Clamp(TimeSinceLastDamage / 3.0f, 0.0f, 1.0f);

	float Score = DistanceScore * 0.3f + HealthScore * 0.2f + RecentDamageScore * 0.5f;
	return FMath::Clamp(Score, 0.0f, 1.0f);
}

// Calculate utility for retreating
float UUtilityFunctionLibrary::CalculateRetreatUtility(float DistanceToPlayer, float Health, float seePlayer)
{
	// High score if far from player, low health, etc.
	float DistanceScore = 1.0f - FMath::Clamp(DistanceToPlayer / 10000.0f, 0.0f, 1.0f);
	float HealthScore = 1.0f - FMath::Clamp(Health, 0.0f, 1.0f);
	float SeeScore = FMath::Clamp(seePlayer, 0.0f, 1.0f);

	float Score = DistanceScore * 0.1f + HealthScore * 0.8f + SeeScore * 0.1f;
	return FMath::Clamp(Score, 0.0f, 1.0f);
}

// Calculate utility for chasing
float UUtilityFunctionLibrary::CalculateChasingUtility(float Health, float seePlayer, float TimeSinceSeenPlayer)
{
	float HealthScore = FMath::Clamp(Health, 0.0f, 1.0f);
	float SeeScore = 1 - FMath::Clamp(seePlayer, 0.0f, 1.0f);
	float NotSeenPlayerScore = FMath::Clamp(TimeSinceSeenPlayer / 5, 0.0f, 1.0f);

	float Score = HealthScore * 0.3 + SeeScore * 0.1 + NotSeenPlayerScore * 0.6;
	return FMath::Clamp(Score, 0.0f, 1.0f);
}

// Calculate utility for blocking an exit
float UUtilityFunctionLibrary::CalculateBlockingExitUtility(float DistanceToExit, float PlayerDistanceToExit)
{
	float DistanceToExitScore = 1 - FMath::Clamp(DistanceToExit / 15000.0f, 0.0f, 1.0f);
	float PlayerThreatScore = 1.0f - FMath::Clamp(PlayerDistanceToExit / 15000.0f, 0.0f, 1.0f);

	// Combine scores with weights
	float Score = DistanceToExitScore * 0.7f + PlayerThreatScore * 0.3f;
	return Score;
}

// Calculate utility for random searching
float UUtilityFunctionLibrary::CalculateRandomSearchUtility(float seePlayer, float TimeSinceSeenPlayer, float Health)
{
	// If health is too low, do not search
	if (Health < 0.2)
	{
		return 0.0f;
	}

	float LostSightScore = 1 - FMath::Clamp(seePlayer, 0.0f, 1.0f);
	float NotSeenPlayerScore = FMath::Clamp(TimeSinceSeenPlayer / 20, 0.0f, 1.0f);

	float Score = NotSeenPlayerScore * 0.4f + LostSightScore * 0.6;
	return Score;
}

// Select action from AI utility scores
EAction UUtilityFunctionLibrary::SelectAction(const TArray<FActionScore>& score, EAction currenAction)
{
	// Sort actions by score descending
	TArray<FActionScore> Sorted = score;
	Sorted.Sort([](const FActionScore& A, const FActionScore& B) { return A.Score > B.Score; });

	// Pick randomly among the top 2 highest scores
	int32 TopN = FMath::Min(2, Sorted.Num());
	int32 Index = FMath::RandRange(0, TopN - 1);
	return Sorted[Index].Action;

	// Alternative: always pick highest score (commented out)
	/*
	if (score.Num() == 0)
		return EAction::Attack;

	float max = -FLT_MAX;
	FActionScore best;
	float currentActionScore = 0.0f;

	for (auto& it : score)
	{
		if (it.Score > max)
		{
			max = it.Score;
			best = it;
		}
		if (it.Action == currenAction)
		{
			currentActionScore = it.Score;
		}
	}

	if (best.Action == currenAction)
		return currenAction;

	currenAction = best.Action;
	return currenAction;
	*/
}