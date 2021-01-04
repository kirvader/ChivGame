// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MainCharacterPawn.generated.h"

class UPaperFlipbookComponent;
class UCameraComponent;
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
	// Инвентарь
	
	// Моделька персонажа
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent *HeroSprite;
	// Корень, так как не нашел способа прикрепить все к рут компоненту
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* HeroStaticMesh;
	// методы двигающие персонажа и камеру
	void CalculateMoveLeftRightInput(float Value);
	void CalculateCameraMoveLeftRightInput();
	void CalculateMoveUpDownInput(float Value);
	void CalculateCameraFOVAndZoom();
	void ZoomCamera();
	
	void MoveHero();
	void MoveCamera();
	void UpdateHeroIsMoving();
	// Скорость персонажа по обеим осям
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeedUpDown = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeedLeftRight = 400.0f;
	// левая и правая границы куда может зайти герой
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float LeftestPosition = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RightestPosition = 0.0f;
	// Для настройки угла наклона плоскости по которой ходит игрок
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float PlaneAngle = 5.f;
	// левая и правая границы куда может зайти камера
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float LeftestCameraPosition = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float RightestCameraPosition = 0.0f;
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
	float RadiansPlaneAngle = 5.f;
	float CurrentCameraFOV = NormalFOV;
	float TargetCameraFOV = NormalFOV;
	// Переменная отвечающая за тип текущего интерактивного объекта, а именно ссылка на него
	// Используется для фокусировки камеры на соответствующем объекте
	
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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	AActor* CurrentInteractiveActor = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	AActor* CurrentInteractiveItem = nullptr;
	
	void SetCurrentInteractiveActor(AActor *ActorRef);

	void SetCurrentInteractiveItem(AActor* ActorRef);
	
	UFUNCTION(BlueprintCallable, BluePrintNativeEvent)
	void InteractTable();

	UFUNCTION(BlueprintCallable, BluePrintNativeEvent)
	void PickUpItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health = 60.f;
	
	UFUNCTION(BlueprintCallable, Category = "Items")
	void UseItem(UItem *Item);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UInventoryComponent *Inventory;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called when E pressed
	void OnInteract();
	void SwitchItem();
	void OnPickUpItemCall();


};
