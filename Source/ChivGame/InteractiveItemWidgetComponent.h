// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "InteractiveItemWidgetComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class CHIVGAME_API UInteractiveItemWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WidgetRelativeLocation", meta = (AllowPrivateAccess = "true"))
		FVector WidgetRelativeLocation = FVector(0, 0, 100);

	UInteractiveItemWidgetComponent();


};
