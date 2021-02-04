// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "ChivGame/PickupableItem.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}

bool UInventoryComponent::AddItem(APickupableItem* Item)
{
	
	if (Item == nullptr || Items.Num() >= Capacity) {
		UE_LOG(LogTemp, Error, TEXT("Item is null"));
		return false;
	}
	// setting up an item
	Item->OwningInventory = this;
	//Item->World = GetWorld();
	
	// adding item to inventory
	if (CurrentItem == nullptr) {
		// if there were not any items
		UE_LOG(LogTemp, Warning, TEXT("size is zero"));

		Item->NextInInventory = Item;
		Item->PrevInInventory = Item;
	}
	else {
		// if there were some items
		UE_LOG(LogTemp, Warning, TEXT("size is not zero"));
		APickupableItem*NextItem = CurrentItem->NextInInventory;
		Item->NextInInventory = NextItem;
		CurrentItem->NextInInventory = Item;
		Item->PrevInInventory = CurrentItem;
		NextItem->PrevInInventory = Item;
	}
	CurrentItem = Item;
	UE_LOG(LogTemp, Warning, TEXT("Current item name = %s"), *(CurrentItem->ItemDisplayName));

	// just to easier explanation
	// can be deleted
	Items.Add(Item);

	return true;
}

bool UInventoryComponent::RemoveItem(APickupableItem* Item)
{
	if (Item) {
		// setting up an item
		Item->OwningInventory = nullptr;
		//Item->World = nullptr;

		// removing an item from inventory
		APickupableItem*NextItem = Item->NextInInventory;
		APickupableItem*PrevItem = Item->PrevInInventory;
		
		if (NextItem == nullptr) {
			// if an item is not in the inventory
			return true;
		}
		if (NextItem == Item) {
			// if that is a last element
			Item->NextInInventory = nullptr;
			Item->PrevInInventory = nullptr;
		} else {
			// if there are more than one item
			NextItem->PrevInInventory = PrevItem;
			PrevItem->NextInInventory = NextItem;

			Item->NextInInventory = nullptr;
			Item->PrevInInventory = nullptr;
		}
		// has to be deleted but later
		Items.RemoveSingle(Item);

		return true;
	}
	return false;
}

void UInventoryComponent::SwitchToNextItem() 
{
	if (CurrentItem == nullptr) return;
	CurrentItem = CurrentItem->NextInInventory;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	
	Super::BeginPlay();
	// ...
	
	
	/*
	FString converted = CurrentItem->PrevInInventory->ItemDisplayName;
	UE_LOG(LogTemp, Warning, TEXT("CurrentItem->Prev->Name = %s\n"), *converted);*/
}

