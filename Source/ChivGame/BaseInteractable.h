// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseInteractable.generated.h"

class UStaticMeshComponent;

UCLASS()
class CHIVGAME_API ABaseInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseInteractable();

	UFUNCTION(BlueprintNativeEvent)
	void Interact();
	virtual void Interact_Implementation();

	UPROPERTY(EditAnywhere, Category = "Interactable Properties")
	UStaticMeshComponent *InteractableMesh;

	UPROPERTY(EditAnywhere, Category = "Interactable Properties")
	FString InteractableHelpText;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
