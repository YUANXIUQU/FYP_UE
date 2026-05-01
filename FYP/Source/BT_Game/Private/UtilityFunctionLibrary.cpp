// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityFunctionLibrary.h"

float UUtilityFunctionLibrary::EvaluateConsideration(float NormalizedValue, UCurveFloat* Curve)
{
	if (!Curve)
	{
		return FMath::Clamp(NormalizedValue, 0.0f, 1.0f);
	}

	return FMath::Clamp(Curve->GetFloatValue(NormalizedValue), 0.0f, 1.0f);
}

float UUtilityFunctionLibrary::CalculateAttackUtility(float DistanceToPlayer, float Health, float seePlayer, UCurveFloat* DistanceCurve)
{
	float NormalizedDistance = FMath::Clamp(DistanceToPlayer / 10000.0f, 0.0f, 1.0f);
	float HealthScore = FMath::Clamp(Health, 0.0f, 1.0f);
	float SeeScore = FMath::Clamp(seePlayer, 0.0f, 1.0f);

	float DistanceScore = EvaluateConsideration(NormalizedDistance, DistanceCurve);

	if (seePlayer <= 0.0f)
	{
		return 0.0f;
	}
	float Score =
		DistanceScore * 0.6f +
		HealthScore * 0.2f +
		SeeScore * 0.2f;

	return FMath::Clamp(Score, 0.0f, 1.0f);
}

float UUtilityFunctionLibrary::CalculateHidingUtility(float DistanceToPlayer, float Health, float TimeSinceLastDamage)
{
	float DistanceScore = 1.0f - FMath::Clamp(DistanceToPlayer / 10000.0f, 0.0f, 1.0f);
	float HealthScore = 1.0f - FMath::Clamp(Health, 0.0f, 1.0f);
	float RecentDamageScore = 1 - FMath::Clamp(TimeSinceLastDamage/3.0f, 0.0f, 1.0f);
	float Score = DistanceScore * 0.3f + HealthScore * 0.2f + RecentDamageScore * 0.5f;
	return FMath::Clamp(Score, 0.0f, 1.0f);
}


float UUtilityFunctionLibrary::CalculateRetreatUtility(float DistanceToPlayer, float Health, float seePlayer)
{
	//Far from Player
	float DistanceScore = 1.0f - FMath::Clamp(DistanceToPlayer / 10000.0f, 0.0f, 1.0f);
	float HealthScore = 1.0f - FMath::Clamp(Health, 0.0f, 1.0f);
	float SeeScore = FMath::Clamp(seePlayer, 0.0f, 1.0f);

	float Score = DistanceScore * 0.1f + HealthScore * 0.8f + SeeScore * 0.1f;
	return FMath::Clamp(Score, 0.0f, 1.0f);
}

float UUtilityFunctionLibrary::CalculateChasingUtility(float Health,float seePlayer, float TimeSinceSeenPlayer)
{
	float HealthScore = FMath::Clamp(Health, 0.0f, 1.0f);
	float SeeScore = 1 - FMath::Clamp(seePlayer, 0.0f, 1.0f);
	float NotSeenPlayerScore = FMath::Clamp(TimeSinceSeenPlayer/5, 0.0f, 1.0f);
	float Score = HealthScore * 0.3 + SeeScore * 0.1 + NotSeenPlayerScore * 0.6;
	return FMath::Clamp(Score, 0.0f, 1.0f);
}

float UUtilityFunctionLibrary::CalculateBlockingExitUtility(float DistanceToExit, float PlayerDistanceToExit)
{
	float DistanceToExitScore = 1 - FMath::Clamp(DistanceToExit / 15000.0f, 0.0f, 1.0f);
	float PlayerThreatScore = 1.0f - FMath::Clamp(PlayerDistanceToExit / 15000.0f, 0.0f, 1.0f);
	float Score = DistanceToExitScore * 0.7f + PlayerThreatScore * 0.3f;
	return Score;
}


float UUtilityFunctionLibrary::CalculateFollowingVIPUtility(float DistanceToPlayer, float DistanceToVIP)
{
	float DistanceToPlayerScore = FMath::Clamp(DistanceToPlayer / 10000.0f, 0.0f,1.0f);
	float DistanceToVIPScore = 1 - FMath::Clamp(DistanceToVIP / 10000.0f, 0.0f, 1.0f);
	float Score = DistanceToPlayerScore * 0.2f + DistanceToVIPScore * 0.8f;
	return Score;
}


float UUtilityFunctionLibrary::CalculateRandomSearchUtility(float seePlayer, float TimeSinceSeenPlayer,float Health)
{
	//Opt Out condition
	if (Health < 0.2)
	{
		return 0.0f;
	}
	float LostSightScore = 1 - FMath::Clamp(seePlayer, 0.0f, 1.0f);
	float NotSeenPlayerScore = FMath::Clamp(TimeSinceSeenPlayer/20, 0.0f, 1.0f);
	float Score = NotSeenPlayerScore * 0.4f + LostSightScore * 0.6;
	return Score;
}

EAction UUtilityFunctionLibrary::SelectAction(const TArray<FActionScore>& score, EAction currenAction)
{
	//Select random action from 2 actions with highest score////////////////////////////
	/*TArray<FActionScore> Sorted = score;

	Sorted.Sort([](const FActionScore& A, const FActionScore& B) {return A.Score > B.Score; });
	int32 TopN = FMath::Min(2, Sorted.Num());
	int32 Index = FMath::RandRange(0, TopN - 1);
	return Sorted[Index].Action;*/

	//Select Highest Score////////////////////////////////////////////////////
	if (score.Num() == 0)
	{
		return EAction::Attack;
	}

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
	//if current action is already the best,then select it
	if (best.Action == currenAction)
	{
		return currenAction;
	}
	/*if (best.Score > currentActionScore)
	{
		currenAction = best.Action;
	}*/
	currenAction = best.Action;
	return currenAction;
}
