// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInteractable.h"
#include "InteractableThing.generated.h"

/**
 * 
 */
UCLASS()
class CHIVGAME_API AInteractableThing : public ABaseInteractable
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AInteractableThing();

	virtual void DefaultAction(AMainCharacterPawn* ActingPlayer) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TextAbout")
		FString UseActionText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TextAbout")
		FString ItemDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TextAbout")
		FString ItemDescription;

	UFUNCTION(BlueprintCallable, BluePrintNativeEvent)
	void InteractiveAction();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
		float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
		TArray<FString> ItemTags;
};
