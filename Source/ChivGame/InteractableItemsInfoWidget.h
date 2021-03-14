// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Components/VerticalBox.h"
#include <Runtime/UMG/Public/Components/WrapBox.h>
#include <ChivGame/InteractableItemsSimpleAction.h>
#include "InteractableItemsInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHIVGAME_API UInteractableItemsInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UWrapBox* PossibleActionsList;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interactive")
		TSubclassOf<UUserWidget> SimpleActionWidgetClass;

	UInteractableItemsInfoWidget(const FObjectInitializer& ObjectInitializer);

	void BuildPossibleActions(ABaseInteractable* CurrentOwner);

	void ShowInfo(FString Name);

	void ShowPossibleActions();

	void HidePossibleActions();

	void HideInfo();

	bool ActionsAreHidden();


};
