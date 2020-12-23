// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "ChivGame/Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

bool UInventoryComponent::AddItem(UItem *Item) 
{
	if (!Item || Items.Num() >= Capacity) {
		return false;
	}
	// setting up an item
	Item->OwningInventory = this;
	Item->World = GetWorld();
	
	// adding item to inventory
	if (CurrentItem == nullptr) {
		// if there were not any items

		Item->NextInInventory = Item;
		Item->PrevInInventory = Item;
	}
	else {
		// if there were some items
		UItem *NextItem = CurrentItem->NextInInventory;
		Item->NextInInventory = NextItem;
		CurrentItem->NextInInventory = Item;
		Item->PrevInInventory = CurrentItem;
		NextItem->PrevInInventory = Item;
	}

	// just to easier explanation
	// can be deleted
	Items.Add(Item);

	// updating UI
	InventoryUpdate();
	return true;
}

bool UInventoryComponent::RemoveItem(UItem *Item) 
{
	if (Item) {
		// setting up an item
		Item->OwningInventory = nullptr;
		Item->World = nullptr;

		// removing an item from inventory
		UItem *NextItem = Item->NextInInventory;
		UItem *PrevItem = Item->PrevInInventory;
		
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

		// updating UI
		InventoryUpdate();
		return true;
	}
	return false;
}

void UInventoryComponent::SwitchToNextItem() 
{
	CurrentItem = CurrentItem->NextInInventory;
}

void UInventoryComponent::InventoryUpdate_Implementation() 
{
	
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}