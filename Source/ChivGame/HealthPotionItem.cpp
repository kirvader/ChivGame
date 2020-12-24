// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPotionItem.h"
#include "ChivGame/MainCharacterPawn.h"


void UHealthPotionItem::Use(AMainCharacterPawn *Character) 
{
    if (Character) {
        Character->Health += Healing;
    }
}
