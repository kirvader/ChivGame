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

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WidgetRelativeLocation", meta = (AllowPrivateAccess = "true"))
		int32 x = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WidgetRelativeLocation", meta = (AllowPrivateAccess = "true"))
		int32 y = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WidgetRelativeLocation", meta = (AllowPrivateAccess = "true"))
		int32 z = 100;

public:

	UInteractiveItemWidgetComponent();

	void InitWidget();

	UFUNCTION(BlueprintCallable)
	FVector GetRelativeVector();
};
