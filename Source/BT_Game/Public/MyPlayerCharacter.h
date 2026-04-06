// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPlayerCharacter.generated.h"

UCLASS()
class BT_GAME_API AMyPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(BlueprintReadOnly, Category="Inventory")
	TMap<FName, int32> ItemCounts;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItem(FName ItemName, int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 GetItemCount(FName ItemName) const;
};
