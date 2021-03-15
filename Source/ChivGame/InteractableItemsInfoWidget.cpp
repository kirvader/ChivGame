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
		AMainCharacterPawn* CurrentPlayer = Cast<AMainCharacterPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		UE_LOG(LogTemp, Warning, TEXT("number of current item possible actions = %d"), CurrentOwner->PossibleActions.Num());
		for (auto action : CurrentOwner->PossibleActions) {
			UInteractableItemsSimpleAction* ActionButton = CreateWidget<UInteractableItemsSimpleAction>(GetWorld(), SimpleActionWidgetClass);
			if (ActionButton) {
				
				ActionButton->ConfigureAction(action, CurrentPlayer, CurrentOwner);
				ActionButton->AddToViewport();
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



