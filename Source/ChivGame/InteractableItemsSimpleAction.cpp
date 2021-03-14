// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableItemsSimpleAction.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "InteractableItemsInfoWidgetComp.h"
#include "BaseInteractable.h"
#include "MainCharacterPawn.h"

UInteractableItemsSimpleAction::UInteractableItemsSimpleAction(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}

void UInteractableItemsSimpleAction::OnActionButtonClicked()
{
	// hide menu
	if (OwnerItem) {
		OwnerItem->InfoWidget->HidePossibleActions();
		// act
		switch (ActionName)
		{
		case Button_Consider:
			OwnerItem->Consider(CurrentPlayer);
			break;
		case Button_Speak:
			OwnerItem->Speak(CurrentPlayer);
			break;
		case Button_PickUp:
			OwnerItem->PickUp(CurrentPlayer);
			break;
		case Button_Use:
			OwnerItem->Use(CurrentPlayer);
			break;
		case Button_ApplyCurrent:
			OwnerItem->ApplyCurrent(CurrentPlayer);
			break;
		default:
			break;
		}
	}

}

void UInteractableItemsSimpleAction::ConfigureAction(TEnumAsByte<InteractableItemActionButton> Action, AMainCharacterPawn* PlayerRef, ABaseInteractable* CurrentOwnerItem)
{
	SetPlayerAndOwnerItem(PlayerRef, CurrentOwnerItem);
	SetAction(Action);
}

void UInteractableItemsSimpleAction::SetPlayerAndOwnerItem(AMainCharacterPawn* PlayerRef, ABaseInteractable* CurrentOwnerItem)
{
	OwnerItem = CurrentOwnerItem;
	CurrentPlayer = PlayerRef;
}

void UInteractableItemsSimpleAction::SetAction(TEnumAsByte<InteractableItemActionButton> Action)  {
	// need to set current player and owner interactable item
	FText ChoosedButtonText = FText::FromString("ActionName");
	UTexture2D* ChoosedButtonIcon = W_ActionButtonIcon;
	ActionName = Action;
	switch (Action)
	{
	case Button_Consider:
		ChoosedButtonText = FText::FromString("Consider");
		ChoosedButtonIcon = W_ActionButtonIcon;
		break;
	case Button_Speak:
		ChoosedButtonText = FText::FromString("Speak");
		ChoosedButtonIcon = A_ActionButtonIcon;
		break;
	case Button_PickUp:
		ChoosedButtonText = FText::FromString("Pick up");
		ChoosedButtonIcon = S_ActionButtonIcon;
		break;
	case Button_Use:
		ChoosedButtonText = FText::FromString("Use");
		ChoosedButtonIcon = S_ActionButtonIcon;
		break;
	case Button_ApplyCurrent:
		ChoosedButtonText = FText::FromString("Apply current item ");
		ChoosedButtonIcon = D_ActionButtonIcon;
		break;
	default:
		ChoosedButtonText = FText::FromString("");
		ChoosedButtonIcon;
		break;
	}
	
	if (SimpleThingActionTextBlock) SimpleThingActionTextBlock->SetText(ChoosedButtonText);
	if (SimpleThingActionButtonImage && ChoosedButtonIcon) SimpleThingActionButtonImage->SetBrushFromTexture(ChoosedButtonIcon);
}