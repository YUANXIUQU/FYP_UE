// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityFunctionLibrary.h"

float UUtilityFunctionLibrary::CalculateAttackUtility(float DistanceToPlayer, float Health, float seePlayer)
{
	float DistanceScore = 1.0f - FMath::Clamp(DistanceToPlayer / 10000.0f, 0.0f, 1.0f);
	float HealthScore = FMath::Clamp(Health, 0.0f, 1.0f);
	float SeeScore = FMath::Clamp(seePlayer, 0.0f, 1.0f);

	float Score =
		DistanceScore * 0.4f +
		HealthScore * 0.3f +
		SeeScore * 0.3f;

	return FMath::Clamp(Score, 0.0f, 1.0f);
}

float UUtilityFunctionLibrary::CalculateHidingUtility(float DistanceToPlayer, float Health, float seePlayer)
{
	float DistanceScore = 1.0f - FMath::Clamp(DistanceToPlayer / 10000.0f, 0.0f, 1.0f);
	float HealthScore = 1.0f - FMath::Clamp(Health, 0.0f, 1.0f);
	float SeeScore = FMath::Clamp(seePlayer, 0.0f, 1.0f);

	float Score = DistanceScore * 0.2f + HealthScore * 0.6f + SeeScore * 0.2f;
	return FMath::Clamp(Score, 0.0f, 1.0f);
}


float UUtilityFunctionLibrary::CalculateRetreatUtility(float DistanceToPlayer, float Health, float seePlayer)
{
	//Far from Player
	float DistanceScore = 1.0f - FMath::Clamp(DistanceToPlayer / 10000.0f, 0.0f, 1.0f);
	float HealthScore = 1.0f - FMath::Clamp(Health, 0.0f, 1.0f);

	float Score = DistanceScore * 0.1f + HealthScore * 0.9f;
	return FMath::Clamp(Score, 0.0f, 1.0f);
}

float UUtilityFunctionLibrary::CalculateChasingUtility(float DistanceToPlayer,float seePlayer)
{
	float DistanceScore = FMath::Clamp(DistanceToPlayer / 10000.0f, 0.0f, 1.0f);
	float SeeScore = 1 - FMath::Clamp(seePlayer, 0.0f, 1.0f);
	float Score = DistanceScore*0.5 + SeeScore * 0.5;
	return FMath::Clamp(Score, 0.0f, 1.0f);
}

float UUtilityFunctionLibrary::CalculateBlockingExitUtility(float DistanceToExit, float DistanceToPlayer)
{
	float DistanceToExitScore = 1 - FMath::Clamp(DistanceToExit / 10000.0f, 0.0f, 1.0f);
	float DistanceToPlayerScore = FMath::Clamp(DistanceToPlayer / 10000.0f, 0.0f, 1.0f);
	float Score = DistanceToExitScore * 0.9f + DistanceToPlayerScore * 0.1f;
	return Score;
}


float UUtilityFunctionLibrary::CalculateFollowingVIPUtility(float DistanceToPlayer, float DistanceToVIP)
{
	float DistanceToPlayerScore = FMath::Clamp(DistanceToPlayer / 10000.0f, 0.0f,1.0f);
	float DistanceToVIPScore = 1 - FMath::Clamp(DistanceToVIP / 10000.0f, 0.0f, 1.0f);
	float Score = DistanceToPlayerScore * 0.2f + DistanceToVIPScore * 0.8f;
	return Score;
}


float UUtilityFunctionLibrary::CalculateRandomSearchUtility(float seePlayer)
{
	float Score = 1-seePlayer;
	return Score;
}

EAction UUtilityFunctionLibrary::SelectAction(const TArray<FActionScore>& score)
{
	//Define a minimum score
	if (score.Num() == 0)
	{
		return EAction::Attack;
	}

	float max = -FLT_MAX; 
	FActionScore best;
	for (auto& it : score)
	{
		if (it.Score > max)
		{
			max = it.Score;
			best = it;
		}
	}

	EAction bestAction = best.Action;
	return bestAction;
}
