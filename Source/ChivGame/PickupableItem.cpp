// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupableItem.h"
#include "MainCharacterPawn.h"

APickupableItem::APickupableItem() {
	
}

void APickupableItem::BeginPlay() {
	Super::BeginPlay();
}

void APickupableItem::DefaultAction(AMainCharacterPawn* ActingPlayer) {
	// as lazy as that is but default action is to pick it up to inventory

	if (ActingPlayer->Inventory->AddItem(this)) {
		SetActorHiddenInGame(true);
		ActingPlayer->RemoveInteractableActor();
	}
	
}