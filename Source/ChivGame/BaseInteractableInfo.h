// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "BaseInteractableInfo.generated.h"

/**
 * 
 */
UCLASS()
class CHIVGAME_API UBaseInteractableInfo : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	UBaseInteractableInfo();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		FVector WidgetInfoRelativeLocation = FVector(0.f, 0.f, 100.f);
};
