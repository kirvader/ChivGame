// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractiveItemWidget.generated.h"

/**
 * https://www.tomlooman.com/creating-actor-widgets-umg/
 */

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOwningActorChanged, AActor*, NewOwner); 
/** 
 * Is mostly like: void FOnOwningActorChanged(AActor* NewOwner);
 * multi-cast is for getting by reference (?)
 * See more: https://docs.unrealengine.com/en-US/ProgrammingAndScripting/ProgrammingWithCPP/UnrealArchitecture/Delegates/Multicast/index.html
 * and http://gameue4.blogspot.com/2018/01/sozdanie-delegata-c-ufunction.html (simple explainatation)
 */

UCLASS(Abstract)
class CHIVGAME_API UInteractiveItemWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	/* Actor that widget is attached to via WidgetComponent */
	UPROPERTY(BlueprintReadOnly, Category = "ActorWidget")
		AActor* OwningActor;

public:
	UFUNCTION(BlueprintCallable)
		void SetOwningActor(AActor* NewOwner);

	//UPROPERTY(BlueprintAssignable)
	//	FOnOwningActorChanged OnOwningActorChanged;
};
