// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainCharacterPawn.h"

#include "InteractableItemsSimpleAction.generated.h"

/**
 * 
 */


class UTextBlock;
class UImage;
class UButton;
class ABaseInteractable;


UENUM()
enum InteractableItemActionButton
{
	Button_Consider		UMETA(DisplayName = "Consider"),
	Button_Speak		UMETA(DisplayName = "Speak"),
	Button_PickUp		UMETA(DisplayName = "Pick Up"),
	Button_Use			UMETA(DisplayName = "Use"),
	Button_ApplyCurrent	UMETA(DisplayName = "Applying current item")
};




UCLASS()
class CHIVGAME_API UInteractableItemsSimpleAction : public UUserWidget
{
	GENERATED_BODY()

private:
	ABaseInteractable* OwnerItem;

	AMainCharacterPawn* CurrentPlayer;

public:

	UInteractableItemsSimpleAction(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* SimpleThingActionTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UImage* SimpleThingActionButtonImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* SimpleAcionButton;

	InteractableItemActionButton ActionName;

	UFUNCTION(BlueprintCallable)
		void OnActionButtonClicked();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
		UTexture2D* W_ActionButtonIcon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
		UTexture2D* A_ActionButtonIcon;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
		UTexture2D* S_ActionButtonIcon;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
		UTexture2D* D_ActionButtonIcon;

	void ConfigureAction(TEnumAsByte<InteractableItemActionButton> Action, AMainCharacterPawn* PlayerRef, ABaseInteractable* CurrentOwnerItem);
private:
	void SetAction(TEnumAsByte<InteractableItemActionButton>  Action);

	void SetPlayerAndOwnerItem(AMainCharacterPawn* PlayerRef, ABaseInteractable* CurrentOwnerItem);
	


};
