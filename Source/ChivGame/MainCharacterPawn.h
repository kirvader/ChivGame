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
class USceneComponent;
class UPaperSprite;
class USoundCue;
class UItem;

UCLASS()
class CHIVGAME_API AMainCharacterPawn : public APawn
{
	GENERATED_BODY()
private:
	// Камера
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent *Camera;
	// Моделька персонажа
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent *HeroSprite;
	// Корень, так как не нашел способа прикрепить все к рут компоненту
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* HeroStaticMesh;

	// Метод вычисляющий нужное смещение камеры по горизонтали относительно текущего положения в соответствии с вводом игрока
	void CalculateCameraMoveLeftRightInput();

	// Метод вычисляющий нужное смещение игрока по горизонтали относительно текущего положения в соответствии с вводом игрока
	void CalculateMoveLeftRightInput(float Value);

	// Метод вычисляющий нужное приближение камеры в соответствии с вводом игрока
	void CalculateCameraFOVAndZoom();
	
	// Метод вычисляющий нужное смещение игрока по вертикали относительно текущего положения в соответствии с вводом игрокаvoid CalculateCameraMoveLeftRightInput();
	void CalculateMoveUpDownInput(float Value);

	// Метод, который приближает камеру
	void ZoomCamera();

	// Метод, который двигает героя в соответствии с вводом игрока
	void MoveHero();

	// Метод, который двигает камеру в соответствии с движением игрока
	void MoveCamera();

	// Метод, отвечающий на вопрос двигается ли игрок
	void UpdateHeroIsMoving();

	// Скорость движения персонажа по вертикали
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeedUpDown = 500.0f;
	
	// Скорость движения персонажа по горизонтали
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeedLeftRight = 400.0f;

	// Угол наклона плоскости по которой ходит игрок
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float PlaneAngle = 5.f;

	// Левая и правая границы движения камеры
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float LeftestCameraPosition = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float RightestCameraPosition = 0.0f;

	// Коэффициент задержки движения камеры
	// Для того чтобы камера не сразу ехала за игроком, а с небольшой задержкой
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float CameraLag = 0.6f;

	// Приближенный угол обзора камеры(когда игрок взаимодействует)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float ZoomedFOV = 70.f;
	
	// Нормальный угол обзора камеры
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float NormalFOV = 90.f;
	
	// Коэффициент задержки приближения камеры
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float CameraLagFOV = 0.07f;
	
	// глобальный счетчик смещения камеры (вроде как оптимизация)
	FVector CameraMovementDirection = FVector(0.f, 0.f, 0.f);

	// Переменная отвечающая за тип текущего интерактивного объекта, а именно ссылка на него
	// Используется для фокусировки камеры на соответствующем объекте
	AActor *CurrentInteractiveActor = nullptr;

	// Последний actor, к которому была приближена камера
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	AActor* LastZoomedActor = nullptr;
	
	// Угол наклона плоскости по которой ходит игрок, переведенный в радианы
	float RadiansPlaneAngle = 5.f;

	// Угол обзора камеры, который нужно выстваить в следующий момент
	float CurrentCameraFOV = NormalFOV;

	// Угол обзора камеры, к которому она должна прийти 
	float TargetCameraFOV = NormalFOV;

	// глобальный счетчик смещения персонажа (вроде как оптимизация)
	FVector HeroMoveDirection;


public:
	void SetNormalFOV();
	void SetZoomedFOV();
	
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
	TSet<ABaseInteractable*> CurrentInteractableActors;

	void AddInteractableActor(ABaseInteractable* ActorRef);

	void RemoveInteractableActor(ABaseInteractable* ActorRef);
	
	//// Вызывается при попытке взаимодействовать со статичным объектом на земле
	//UFUNCTION(BlueprintCallable, BluePrintNativeEvent)
	//void InteractTable();

	//// Вызывается при попытке подобрать элемент с земли
	//UFUNCTION(BlueprintCallable, BluePrintNativeEvent)
	//void PickUpItem();

	// Текущее хп героя
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health = 60.f;
	
	// Вызывается при попытке использовать предмет из инвентаря
	UFUNCTION(BlueprintCallable, Category = "Items")
	void UseItem(UItem *Item);

	// Указатель на инвентарь игрока
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UInventoryComponent *Inventory;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called when E pressed
	//void OnInteract();

	void SwitchItem();

	void CallWidget();

	//void OnPickUpItemCall();

};
