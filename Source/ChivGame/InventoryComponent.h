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
	bool AddItem(UItem *Item);
	bool RemoveItem(UItem *Item);

	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<UItem *> DefaultItems;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	int32 Capacity;
	
	UFUNCTION(BlueprintCallable, BluePrintNativeEvent)
	void InventoryUpdate();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	TArray<UItem *> Items;

	void SwitchToNextItem();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	UItem *CurrentItem = nullptr;

	void TestFunction();
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

		
};
