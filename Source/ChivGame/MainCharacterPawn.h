// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MainCharacterPawn.generated.h"

class UPaperFlipbookComponent;
class UCameraComponent;
class ABaseInteractable;
class ABaseInteractable;
class UInventoryComponent;
class UStaticMeshComponent;
class UCharacterCameraComponent;
class USceneComponent;
class UPaperSprite;
class USoundCue;
class UItem;

UCLASS()
class CHIVGAME_API AMainCharacterPawn : public APawn
{
	GENERATED_BODY()
private:
	
	// Моделька персонажа
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* HeroSprite;
	// Камера персонажа
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCharacterCameraComponent* Camera;
	// Корень, так как не нашел способа прикрепить все к рут компоненту
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* HeroStaticMesh;

	// Метод вычисляющий нужное смещение игрока по горизонтали относительно текущего положения в соответствии с вводом игрока
	void CalculateMoveLeftRightInput(float Value);
	
	// Метод вычисляющий нужное смещение игрока по вертикали относительно текущего положения в соответствии с вводом игрокаvoid CalculateCameraMoveLeftRightInput();
	void CalculateMoveUpDownInput(float Value);

	// Метод, который двигает героя в соответствии с вводом игрока
	void MoveHero();

	// Метод, отвечающий на вопрос двигается ли игрок
	void UpdateHeroIsMoving();

	// Функция отвечающая на вопрос "нужен ли зум?"
	bool NeedZoom();

	// Скорость движения персонажа по вертикали
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeedUpDown = 500.0f;
	
	// Скорость движения персонажа по горизонтали
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeedLeftRight = 400.0f;

	// Угол наклона плоскости по которой ходит игрок
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float PlaneAngle = 5.f;


	// Переменная отвечающая за тип текущего интерактивного объекта, а именно ссылка на него
	// Используется для фокусировки камеры на соответствующем объекте
	AActor *CurrentInteractiveActor = nullptr;

	// Угол наклона плоскости по которой ходит игрок, переведенный в радианы
	float RadiansPlaneAngle = 5.f;

	// глобальный счетчик смещения персонажа (вроде как оптимизация)
	FVector HeroMoveDirection;


public:
	
	// Sets default values for this pawn's properties
	AMainCharacterPawn();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Нужно ли слышать звук шагов в данный момент
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	bool PlayerIsMoving;
	
	// Статичный объект на земле с которым можно взаимодействовать
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")

	ABaseInteractable* CurrentInteractableActor;

	void SetInteractableActor(ABaseInteractable* ActorRef);

	void RemoveInteractableActor();

	void OnDefaultAction();
	
	// Вызывается при попытке взаимодействовать со статичным объектом на земле
	UFUNCTION(BlueprintCallable, BluePrintNativeEvent)
	void InteractTable(ABaseInteractable* InteractableThing);

	// Вызывается при попытке подобрать элемент с земли
	UFUNCTION(BlueprintCallable, BluePrintNativeEvent)
		void UpdateActiveItem();


	// Текущее хп героя
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health = 60.f;
	
	

	// Указатель на инвентарь игрока
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UInventoryComponent *Inventory;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called when E pressed
	void OnInteract();

	void SwitchItem();

	// void CallWidget();

	void OnPickUpItemCall();

};
