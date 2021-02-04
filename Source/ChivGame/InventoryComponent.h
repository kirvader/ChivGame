// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


class UItem;
class APickupableItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHIVGAME_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UFUNCTION(BlueprintCallable)
	bool AddItem(APickupableItem* Item);
	UFUNCTION(BlueprintCallable)
	bool RemoveItem(APickupableItem* Item);

	//// Предметы, которые даются в начале по сценарию
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Items")
	//TArray<TSubclassOf<APickupableItem> > DefaultItems;
	
	// Вместимость инвентаря
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	int32 Capacity = 5;
	
	// Текущие предметы игрока. Нужны для лучшего понимания-отображения в игре
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
	TArray<APickupableItem*> Items;

	UFUNCTION(BlueprintCallable)
	void SwitchToNextItem();
	
	// Предмет, который игрок держит в руках
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
		APickupableItem* CurrentItem = nullptr;

	

protected:

	//// Функция, которая добавляет все начальные предметы в инвентарь.
	//// Так как здесь инвентарь - это двусвязный список, то это немного труднее, чем просто 1 команда
	//void AddDefaults();

	// Called when the game starts
	virtual void BeginPlay() override;


		
};
