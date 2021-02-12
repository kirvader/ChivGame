// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableItemsInfoWidget.h"
#include "Components/TextBlock.h"

UInteractableItemsInfoWidget::UInteractableItemsInfoWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	
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



