// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableItemsInfoWidgetComp.h"
#include "InteractableItemsInfoWidget.h"
#include "Components/ShapeComponent.h"
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
        ABaseInteractable* CurrentOwner = Cast<ABaseInteractable>(GetOwner());
        if (CurrentOwner) {
            /** Make sure widget was created */
            if (InfoWidget)
            {
                UE_LOG(LogTemp, Error, TEXT("in %s build possible actions"), *CurrentOwner->ItemDisplayName);
                InfoWidget->BuildPossibleActions(CurrentOwner);
                /** Add it to the viewport */
                // InfoWidget->AddToPlayerScreen();
                SetWidget(InfoWidget);
            }
        }
    }

    ABaseInteractable* CurrentOwner = Cast<ABaseInteractable>(GetOwner());

    if (CurrentOwner) {
        FVector Scale = CurrentOwner->TriggerShape->GetComponentScale();
        SetRelativeLocation(FVector(Scale.X * CurrentOwner->TriggerExtent.X / 2 + 50, 10.f, Scale.Z * CurrentOwner->TriggerExtent.Z / 2 + 50));
    }
    SetWorldRotation(FRotator(0.f, 90.f, 0.f));
    SetWorldScale3D(FVector(2.f, 2.f, 2.f));
}

void UInteractableItemsInfoWidgetComp::ShowInfo()
{
    ABaseInteractable* CurrentOwner = Cast<ABaseInteractable>(GetOwner());
    UE_LOG(LogTemp, Warning, TEXT("name - %s"), *CurrentOwner->ItemDisplayName);
    if (InfoWidget)
        InfoWidget->ShowInfo(CurrentOwner->ItemDisplayName);
}

void UInteractableItemsInfoWidgetComp::ShowPossibleActions()
{
    if (InfoWidget) {
        InfoWidget->ShowPossibleActions();
    }
}

 void UInteractableItemsInfoWidgetComp::HideInfo()
{
     if (InfoWidget) 
        InfoWidget->HideInfo();
}

 void UInteractableItemsInfoWidgetComp::HidePossibleActions()
 {
     if (InfoWidget) {
         InfoWidget->HidePossibleActions();
     }
 }

 bool UInteractableItemsInfoWidgetComp::ActionsAreHidden()
 {
     return InfoWidget->ActionsAreHidden();
 }




