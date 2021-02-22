// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableItemsInfoWidget.h"
#include "Components/TextBlock.h"
#include "BaseInteractable.h"
#include "MainCharacterPawn.h"

#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

UInteractableItemsInfoWidget::UInteractableItemsInfoWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	
}

void UInteractableItemsInfoWidget::BuildPossibleActions(ABaseInteractable* CurrentOwner) {
	PossibleActionsList->ClearChildren();
	if (CurrentOwner) {
		for (auto action : CurrentOwner->PossibleActions) {
			UInteractableItemsSimpleAction* ActionButton = CreateWidget<UInteractableItemsSimpleAction>(GetWorld(), SimpleActionWidgetClass);
			if (ActionButton) {
				AMainCharacterPawn* CurrentPlayer = Cast<AMainCharacterPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
				ActionButton->ConfigureAction(action, CurrentPlayer, CurrentOwner);
				PossibleActionsList->AddChildToWrapBox(ActionButton);
			}
		}
	}
}

void UInteractableItemsInfoWidget::ShowInfo(FString Name)
{
	if (ItemName) {
		ItemName->SetVisibility(ESlateVisibility::Visible);
		ItemName->SetText(FText::FromString(Name));
	}
}

void UInteractableItemsInfoWidget::ShowPossibleActions()
{
	if (PossibleActionsList) {
		PossibleActionsList->SetVisibility(ESlateVisibility::Visible);
	}
}

void UInteractableItemsInfoWidget::HidePossibleActions()
{
	if (PossibleActionsList) {
		PossibleActionsList->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UInteractableItemsInfoWidget::HideInfo()
{
	if (ItemName) {
		ItemName->SetVisibility(ESlateVisibility::Hidden);
		HidePossibleActions();
	}
}

bool UInteractableItemsInfoWidget::ActionsAreHidden()
{
	return (PossibleActionsList->Visibility == ESlateVisibility::Hidden);
}



