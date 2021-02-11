// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableItemsInfoWidgetComp.h"
#include "InteractableItemsInfoWidget.h"
#include "BaseInteractable.h"



UInteractableItemsInfoWidgetComp::UInteractableItemsInfoWidgetComp() {
    SetDrawAtDesiredSize(true);
    SetWidgetSpace(EWidgetSpace::World);
    SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void UInteractableItemsInfoWidgetComp::BeginPlay()
{

    if (InfoWidgetClass)
    {
        InfoWidget = CreateWidget<UInteractableItemsInfoWidget>(GetWorld(), InfoWidgetClass);
        /** Make sure widget was created */
        if (InfoWidget)
        {
            /** Add it to the viewport */
            // InfoWidget->AddToPlayerScreen();
            SetWidget(InfoWidget);
        }
    }

    SetRelativeLocation(FVector(0.f, 0.f, 100.f));
    SetWorldRotation(FRotator(0.f, 90.f, 0.f));
}

void UInteractableItemsInfoWidgetComp::ShowInfo()
{
    ABaseInteractable* CurrentOwner = Cast<ABaseInteractable>(GetOwner());
    UE_LOG(LogTemp, Warning, TEXT("%s"), *CurrentOwner->ItemDisplayName);
    if (InfoWidget)
        InfoWidget->ShowInfo(CurrentOwner->ItemDisplayName);
}

 void UInteractableItemsInfoWidgetComp::HideInfo()
{
     if (InfoWidget)
        InfoWidget->HideInfo();
}


