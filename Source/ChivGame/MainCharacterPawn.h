// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MainCharacterPawn.generated.h"

class UPaperFlipbookComponent;
class UCameraComponent;
class UStaticMeshComponent;

UCLASS()
class CHIVGAME_API AMainCharacterPawn : public APawn
{
	GENERATED_BODY()
private:
	// Камера
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent *Camera;
	// Sprite
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent *Sprite;
	// StaticMesh = RootComponent
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* HeroStaticMesh;
	void CalculateMoveLeftRightInput(float Value);
	void CalculateMoveUpDownInput(float Value);
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
