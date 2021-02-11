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
		UE_LOG(LogTemp, Warning, TEXT("_____ %s is %s"), *Name, *((FText::FromString(Name)).ToString()));
	}
}

void UInteractableItemsInfoWidget::HideInfo()
{
	if (ItemName) {
		ItemName->SetVisibility(ESlateVisibility::Hidden);
	}
}



