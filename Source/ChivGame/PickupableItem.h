// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInteractable.h"
#include "InventoryComponent.h"
#include "PickupableItem.generated.h"

/**
 * 
 */

class AMainCharacterPawn;
UCLASS(Blueprintable)
class CHIVGAME_API APickupableItem : public ABaseInteractable
{
	GENERATED_BODY()
	

protected:
	
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	APickupableItem();

	virtual void DefaultAction(AMainCharacterPawn* ActingPlayer) override;

	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
		UStaticMesh* PickupMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
		UTexture2D* InventoryImage;

	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
		float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
		TArray<FString> ItemTags;

	UPROPERTY()
		UInventoryComponent* OwningInventory;

	APickupableItem* NextInInventory = nullptr;
	APickupableItem* PrevInInventory = nullptr;

	virtual void Use(AMainCharacterPawn* Character) PURE_VIRTUAL(UItem, );

	UFUNCTION(BlueprintImplementableEvent)
		void OnUse(AMainCharacterPawn* Character);
};
