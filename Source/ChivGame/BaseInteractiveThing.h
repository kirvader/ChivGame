// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "InteractiveItemWidgetComponent.h"
#include "BaseInteractiveThing.generated.h"

class UPaperSpriteComponent;

UCLASS()
class CHIVGAME_API ABaseInteractiveThing : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseInteractiveThing();
	/** Shape of the trigger volume component. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	UShapeComponent* Shape = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	UPaperSpriteComponent *Sprite;
	
	/**
	 * Material attached to sprite
	 * Great example on https://github.com/Harrison1/unrealcpp/tree/master/ChangeMaterialMesh
	 * Example of creating shimmering materials showed here: https://www.youtube.com/watch?v=gDa5E1ndGG8
	 */	
	UPROPERTY(EditAnywhere, Category = "Setup")
	UMaterialInterface* ShimmeryMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	UInteractiveItemWidgetComponent* Widget = nullptr;
	
	/** Creates a custom UShapeComponent to represent the trigger volume. */
	UFUNCTION()
	void SetupShapeComponent();
	/** Delegate for Shape's overlap begin event. */
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
	void BindTriggerCallbacksToShape();
	
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
