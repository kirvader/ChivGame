// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueSystemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHIVGAME_API UDialogueSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDialogueSystemComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interactive")
		TSubclassOf<UUserWidget> DialogueWindowAppearance;

private:
	int CurrentConversationID = 0;
	
	int CurrentLineNumber = -1; // -1 - nothing shows

	UUserWidget* CurrentShowingWidget = nullptr;



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

