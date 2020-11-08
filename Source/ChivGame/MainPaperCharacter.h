// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "MainPaperCharacter.generated.h"
class UPaperFlipbookComponent;

UCLASS()
class CHIVGAME_API AMainPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()

private:
	FVector MovePoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeedUpDown = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeedLeftRight = 100.0f;

	UPaperFlipbookComponent* HeroFlipBook;

	void CalculateMoveLeftRightInput(float Value);
	void CalculateMoveUpDownInput(float Value);

	void Move();

public:

	AMainPaperCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
};
