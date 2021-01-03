// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "ChivGame/Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	//AddDefaults();

	//int sz = Items.Num();
	//UE_LOG(LogTemp, Warning, TEXT("size is %d\n"), sz); // size is 0


	//if (CurrentItem == nullptr) {
	//	UE_LOG(LogTemp, Warning, TEXT("Current Item Name nullptr"));
	//	return;
	//}
	//FString converted = CurrentItem->ItemDisplayName;
	//UE_LOG(LogTemp, Warning, TEXT("Current Item Name %s"), *converted);
	
	// ...
}

bool UInventoryComponent::AddItem(UItem *Item) 
{
	
	if (Item == nullptr || Items.Num() >= Capacity) {
		UE_LOG(LogTemp, Error, TEXT("Item is zero"));
		return false;
	}
	// setting up an item
	Item->OwningInventory = this;
	Item->World = GetWorld();
	
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
		UItem *NextItem = CurrentItem->NextInInventory;
		Item->NextInInventory = NextItem;
		CurrentItem->NextInInventory = Item;
		Item->PrevInInventory = CurrentItem;
		NextItem->PrevInInventory = Item;
	}
	CurrentItem = Item;

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
	if (CurrentItem == nullptr) return;
	CurrentItem = CurrentItem->NextInInventory;
}

void UInventoryComponent::InventoryUpdate_Implementation() 
{
	
}

void UInventoryComponent::AddDefaults()
{
	for (TSubclassOf<UItem> item : DefaultItems) {
		if (!item->IsValidLowLevel()) continue;

		UItem* ConvertedItem = NewObject<UItem>(this, item->GetFName(), RF_NoFlags, item.GetDefaultObject());
		/*FString converted = item->ItemDisplayName;*/
		UE_LOG(LogTemp, Warning, TEXT("lol\n"));

		AddItem(ConvertedItem);
	} // adding default items
}



// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	
	Super::BeginPlay();
	// ...
	AddDefaults();
	
	
	/*AddDefaults();



	int sz = DefaultItems.Num();
	for (auto& item : Items) {
		FString converted = item->ItemDisplayName;
		UE_LOG(LogTemp, Warning, TEXT("%s\n"), *converted);
	}
	UE_LOG(LogTemp, Warning, TEXT("size is %d\n"), sz);
	if (CurrentItem->PrevInInventory == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("CurrentItem->Prev = nullptr\n"));
		return;
	}
	FString converted = CurrentItem->PrevInInventory->ItemDisplayName;
	UE_LOG(LogTemp, Warning, TEXT("CurrentItem->Prev->Name = %s\n"), *converted);*/
}

//#if WITH_EDITOR
//void UInventoryComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
//{
//	Super::PostEditChangeProperty(PropertyChangedEvent);
//	AddDefaults();
//
//	int sz = Items.Num();
//	UE_LOG(LogTemp, Warning, TEXT("size is %d\n"), sz); // size is 0
//
//
//	if (CurrentItem == nullptr) {
//		UE_LOG(LogTemp, Warning, TEXT("Current Item Name nullptr"));
//		return;
//	}
//	FString converted = CurrentItem->ItemDisplayName;
//	UE_LOG(LogTemp, Warning, TEXT("Current Item Name %s"), *converted);
//}
//#endif