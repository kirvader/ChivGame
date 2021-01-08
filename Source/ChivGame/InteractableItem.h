// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableItem.generated.h"

class UItem;
class UPaperSpriteComponent;
class UShapeComponent;

UCLASS()
class CHIVGAME_API AInteractableItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableItem();

	// Предмет, который добавят в инвентарь
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	UItem* CastedItemInInventory = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Функция, устанавливающая область триггера
	void SetupShapeComponent();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Блупринтовый ввод предмета инвентаря
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	TSubclassOf<UItem> ItemInInventory;

	// Спрайт поднимаемого элемента в мире
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	UPaperSpriteComponent *ItemSprite;

	// область в которой объект поднимаем
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	UShapeComponent* TriggerShape = nullptr;

	// Метод вызывающийся при входе кого-то в триггер
	UFUNCTION()
	void OnTriggerOverlapBegin
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
	void OnTriggerOverlapEnd
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


	DECLARE_EVENT(ASimpleTriggerVolume, FSimpleTriggerVolumeEvent)
	FSimpleTriggerVolumeEvent TriggerOverlapBeginEvent;
	FSimpleTriggerVolumeEvent TriggerOverlapEndEvent;
};
