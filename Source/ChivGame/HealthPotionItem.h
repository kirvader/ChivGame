// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "HealthPotionItem.generated.h"

/**
 * 
 */
UCLASS()
class CHIVGAME_API UHealthPotionItem : public UItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characteristics")
	float Healing = 10.f;
	
protected:
	virtual void Use(AMainCharacterPawn *Character) override;
};
