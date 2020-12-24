 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

class UInventoryComponent;
class UStaticMesh;
class UTexture2D;
class AMainCharacterPawn;

UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class CHIVGAME_API UItem : public UObject
{
	GENERATED_BODY()

public:
	UItem();

	virtual UWorld *GetWorld() const {return World;}

	UPROPERTY(Transient)
	UWorld *World;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TextAbout")
	FText UseActionText;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	UStaticMesh *PickupMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	UTexture2D *InventoryImage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TextAbout")
	FText ItemDisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TextAbout")
	FText ItemDescription;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	float Weight;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	TArray<FText> Tags;
	
	UPROPERTY()
	UInventoryComponent *OwningInventory;

	UItem *NextInInventory = nullptr;
	UItem *PrevInInventory = nullptr;

	virtual void Use(AMainCharacterPawn *Character) PURE_VIRTUAL(UItem, );

	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(AMainCharacterPawn *Character);
};
