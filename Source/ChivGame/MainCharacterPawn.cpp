// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterPawn.h"
#include "Camera/CameraComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMainCharacterPawn::AMainCharacterPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HeroStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
	RootComponent = HeroStaticMesh;

	Sprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	Sprite->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMainCharacterPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
    PlayerInputComponent->BindAxis("MoveUpAndDown", this, &AMainCharacterPawn::CalculateMoveUpDownInput);
    PlayerInputComponent->BindAxis("MoveLeftAndRight", this, &AMainCharacterPawn::CalculateMoveLeftRightInput);
}

void AMainCharacterPawn::CalculateMoveLeftRightInput(float Value) 
{
    FVector MovePoint = FVector(Value * MoveSpeedLeftRight * GetWorld()->DeltaTimeSeconds, 0, 0);
	Sprite->AddLocalOffset(MovePoint, true);
}

void AMainCharacterPawn::CalculateMoveUpDownInput(float Value) 
{
    FVector MovePoint = FVector(0, -Value * MoveSpeedUpDown * GetWorld()->DeltaTimeSeconds, Value * MoveSpeedUpDown * GetWorld()->DeltaTimeSeconds);
    Sprite->AddLocalOffset(MovePoint, true);
}
