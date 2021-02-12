// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseInteractable.generated.h"

class UInteractiveItemWidgetComponent;
class UMaterialInterface;
class UPaperSpriteComponent;
class UShapeComponent;
class UItem;
class AMainCharacterPawn;
class UBaseInteractableInfo;
class UInteractableItemsInfoWidgetComp;

UCLASS(Abstract)
class CHIVGAME_API ABaseInteractable : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Функция, устанавливающая область триггера
	void SetupShapeComponent();

public:	
	// Sets default values for this actor's properties
	ABaseInteractable();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
		UInteractableItemsInfoWidgetComp* InfoWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TextAbout")
		FString UseActionText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TextAbout")
		FString ItemDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TextAbout")
		FString ItemDescription;

	// Спрайт элемента в мире. nullptr если не нужен
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	UPaperSpriteComponent* ItemSprite = nullptr;

	// область в которой объект поднимаем
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
		UShapeComponent* TriggerShape = nullptr;

	// Метод вызывающийся при входе кого-то в триггер
	UFUNCTION()
		virtual void OnTriggerOverlapBegin
		(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep, const
			FHitResult& SweepResult
		);

	// Начальные размеры области триггера
	UPROPERTY(EditAnywhere, Category = "Geometry")
		FVector TriggerExtent = FVector(50.f, 50.f, 20.f);

	/** Delegate for Shape's overlap end event. */
	UFUNCTION()
		virtual void OnTriggerOverlapEnd
		(
			UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex
		);
	/** Adds callbacks to the shape component's
	 * begin and end overlap events. */
	UFUNCTION()
		void BindTriggerCallbacksToTriggerShape();

	/** Defines, to which actor this trigger should react to.
		 If nullptr, all actors are accepted. */
	UPROPERTY(EditAnywhere, Category = "Setup")
		AActor* ActorThatTriggers = nullptr;

	/** Is run, when OnComponentBeginOverlap()
		 is called. Override to add functionality. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void TriggerCallbackOn();

	/** Is run, when OnComponentEndOverlap() is
		called. Override to add functionality. */
	UFUNCTION()
		virtual void TriggerCallbackOff();

	virtual void DefaultAction(AMainCharacterPawn* ActingPlayer);

	void TogglePossibleAcions();


	DECLARE_EVENT(ASimpleTriggerVolume, FSimpleTriggerVolumeEvent)
	FSimpleTriggerVolumeEvent TriggerOverlapBeginEvent;
	FSimpleTriggerVolumeEvent TriggerOverlapEndEvent;

};
