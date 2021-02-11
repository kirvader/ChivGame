// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "InteractableItemsInfoWidget.h"
#include "InteractableItemsInfoWidgetComp.generated.h"


/**
 * 
 */
UCLASS()
class CHIVGAME_API UInteractableItemsInfoWidgetComp : public UWidgetComponent
{
	GENERATED_BODY()
	

public:
	UInteractableItemsInfoWidgetComp();

	FString ItemName = "Name";

	UPROPERTY(EditDefaultsOnly, Category = "Interactive")
		TSubclassOf<UUserWidget> InfoWidgetClass;

	virtual void BeginPlay() override;

	void ShowInfo();

	void HideInfo();

private:
	UInteractableItemsInfoWidget* InfoWidget;
};
