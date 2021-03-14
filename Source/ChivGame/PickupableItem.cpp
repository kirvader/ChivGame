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

void APickupableItem::Consider(AMainCharacterPawn* ActingPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("Consider %s"), *ItemDisplayName);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Consider %s"), *ItemDisplayName));
}

void APickupableItem::Speak(AMainCharacterPawn* ActingPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("Speak to %s"), *ItemDisplayName);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Speak to %s"), *ItemDisplayName));
}

void APickupableItem::PickUp(AMainCharacterPawn* ActingPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("Pick Up %s"), *ItemDisplayName);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Pick Up %s"), *ItemDisplayName));
	if (ActingPlayer->Inventory->AddItem(this)) {
		SetActorHiddenInGame(true);
		ActingPlayer->RemoveInteractableActor();
	}
}

void APickupableItem::Use(AMainCharacterPawn* ActingPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("Use %s"), *ItemDisplayName);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Use %s"), *ItemDisplayName));
}

void APickupableItem::ApplyCurrent(AMainCharacterPawn* ActingPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("Apply Current to %s"), *ItemDisplayName);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Apply current to %s"), *ItemDisplayName));
}

