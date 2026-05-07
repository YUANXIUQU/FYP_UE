// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerCharacter.h"

// Sets default values
AMyPlayerCharacter::AMyPlayerCharacter()
{
    // Enable Tick() every frame. Turn off if not needed for performance.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
    // You can add initialization code here
}

// Add items to the player's inventory
void AMyPlayerCharacter::AddItem(FName ItemName, int32 Amount)
{
    // Ignore invalid items or non-positive amounts
    if (ItemName.IsNone() || Amount <= 0)
    {
        return;
    }

    // Find existing count or add new entry, then increase by Amount
    int32& Count = ItemCounts.FindOrAdd(ItemName);
    Count += Amount;
}

// Get the number of a specific item in the player's inventory
int32 AMyPlayerCharacter::GetItemCount(FName ItemName) const
{
    // Return the stored count if the item exists
    if (const int32* Found = ItemCounts.Find(ItemName))
    {
        return *Found;
    }

    // Item not found, return 0
    return 0;
}