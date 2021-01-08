// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


class UItem;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHIVGAME_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UFUNCTION(BlueprintCallable)
	bool AddItem(UItem *Item);
	UFUNCTION(BlueprintCallable)
	bool RemoveItem(UItem *Item);

	// Предметы, которые даются в начале по сценарию
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Items")
	TArray<TSubclassOf<UItem> > DefaultItems;
	
	// Вместимость инвентаря
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	int32 Capacity = 20;
	
	// Текущие предметы игрока. Нужны для лучшего понимания-отображения в игре
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
	TArray<UItem *> Items;

	UFUNCTION(BlueprintCallable)
	void SwitchToNextItem();
	
	// Предмет, который игрок держит в руках
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	UItem *CurrentItem = nullptr;

	

protected:

	// Функция, которая добавляет все начальные предметы в инвентарь.
	// Так как здесь инвентарь - это двусвязный список, то это немного труднее, чем просто 1 команда
	void AddDefaults();

	// Called when the game starts
	virtual void BeginPlay() override;


		
};
