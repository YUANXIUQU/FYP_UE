// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerCharacter.h"

// Sets default values
AMyPlayerCharacter::AMyPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyPlayerCharacter::AddItem(FName ItemName, int32 Amount)
{
    if (ItemName.IsNone() || Amount <= 0)
    {
        return;
    }

    int32& Count = ItemCounts.FindOrAdd(ItemName);
    Count += Amount;
}

int32 AMyPlayerCharacter::GetItemCount(FName ItemName) const
{
    if (const int32* Found = ItemCounts.Find(ItemName))
    {
        return *Found;
    }

    return 0;
}
