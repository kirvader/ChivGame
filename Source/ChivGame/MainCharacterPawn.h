// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MainCharacterPawn.generated.h"

class UPaperFlipbookComponent;
class UCameraComponent;
class UStaticMeshComponent;
class USceneComponent;
class UPaperSprite;

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
	// методы двигающие персонажа и камеру
	void CalculateMoveLeftRightInput(float Value);
	void CalculateCameraMoveLeftRightInput();
	void CalculateMoveUpDownInput(float Value);
	void CalculateCameraZoomWhenPlayerIsNear();
	void MoveHero();
	void MoveCamera();
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
	float RadiansPlaneAngle = 5.f;
	UPaperSprite *BackgroundSprite;
	FVector HeroMoveDirection;
	// Четверть экрана за этой полосой(по оси Z) TODO() - автоматизировать его нахождение
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float ZFourth = -600.f;
	// линия по которой движется не приближенная камера
	FVector NormalCameraLinePosition = FVector(0.f, 1440.f, 16.f);
	// линия по которой движется приближенная камера
	FVector ZoomedCameraLinePosition = FVector(0.f, 960.f, -230.f);
	// глобальный счетчик смещения камеры (вроде как оптимизация)
	FVector CameraMovementDirection = FVector(0.f, 0.f, 0.f);
	



public:
	// Sets default values for this pawn's properties
	AMainCharacterPawn();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
