// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
		class UTextBlock* ItemName;

	void ShowInfo(FString Name);

	void HideInfo();


};
