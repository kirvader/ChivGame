// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MainCharacterPawn.generated.h"

class UPaperFlipbookComponent;
class UCameraComponent;
class UStaticMeshComponent;
class USceneComponent;

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
	UPaperFlipbookComponent *Sprite;
	// Корень, так как не нашел способа прикрепить все к рут компоненту
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* HeroStaticMesh;
	// методы двигающие персонажа и камеру
	void CalculateMoveLeftRightInput(float Value);
	void CameraMoveLeftRightInput();
	void CalculateMoveUpDownInput(float Value);
	// Скорость персонажа по обеим осям
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeedUpDown = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeedLeftRight = 400.0f;
	// левая и правая границы куда может зайти герой
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float LeftestPosition = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float RightestPosition = 0.0f;
	// левая и правая границы куда может зайти камера
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float LeftestCameraPosition = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float RightestCameraPosition = 0.0f;
	// Для того чтобы камера не сразу ехала за игроком, а с небольшой задержкой
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float CameraLag = 0.6f;

public:
	// Sets default values for this pawn's properties
	AMainCharacterPawn();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Функция, настраиваемая из блупринтов, для приостановки игры и последующего продолжения
	/*
	* UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Character")
	* void PauseGame();
	* UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Character")
	* void UnpauseGame();
	*/
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
