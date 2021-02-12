// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Components/VerticalBox.h"
#include "InteractableItemsInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHIVGAME_API UInteractableItemsInfoWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UInteractableItemsInfoWidget(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UVerticalBox* PossibleActionsList;

	void ShowInfo(FString Name);

	void ShowPossibleActions();

	void HidePossibleActions();

	void HideInfo();

	bool ActionsAreHidden();


};
