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

UCLASS(Abstract)
class CHIVGAME_API ABaseInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseInteractable();

	// ����������� �������, ������� ������� � ���������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	UItem* CastedItemInInventory = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// �������, ��������������� ������� ��������
	void SetupShapeComponent();

public:	
	// �������� �������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	FString TestingString = "lol, that's working";

	// ������������ ���� �������� ���������. nullptr ���� �� �����������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	TSubclassOf<UItem> ItemInInventory = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	UTexture2D* ActionImage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	FString ActionText;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	FString ActionDescription;

	// ������ �������� � ����. nullptr ���� �� �����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
	UPaperSpriteComponent* ItemSprite = nullptr;

	// ������� � ������� ������ ���������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
		UShapeComponent* TriggerShape = nullptr;

	/**
	 * Material attached to sprite
	 * Great example on https://github.com/Harrison1/unrealcpp/tree/master/ChangeMaterialMesh
	 * Example of creating shimmering materials showed here: https://www.youtube.com/watch?v=gDa5E1ndGG8
	 */
	// Shimmering shader
	UPROPERTY(EditAnywhere, Category = "Setup")
		UMaterialInterface* ShimmeryMaterial = nullptr;

	// Menu widget 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup", meta = (AllowPrivateAccess = "true"))
		UInteractiveItemWidgetComponent* Widget = nullptr;

	// ����� ������������ ��� ����� ����-�� � �������
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

	// ��������� ������� ������� ��������
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


	DECLARE_EVENT(ASimpleTriggerVolume, FSimpleTriggerVolumeEvent)
	FSimpleTriggerVolumeEvent TriggerOverlapBeginEvent;
	FSimpleTriggerVolumeEvent TriggerOverlapEndEvent;

};
