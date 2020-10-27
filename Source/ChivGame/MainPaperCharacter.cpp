// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


AMainPaperCharacter::AMainPaperCharacter()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void AMainPaperCharacter::BeginPlay()
{
    Super::BeginPlay();

    HeroFlipBook = Cast<UPaperFlipbookComponent>(GetSprite());
}

// Called every frame
void AMainPaperCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    Move();
}

// Called to bind functionality to input
void AMainPaperCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveUpAndDown", this, &AMainPaperCharacter::CalculateMoveUpDownInput);
    PlayerInputComponent->BindAxis("MoveLeftAndRight", this, &AMainPaperCharacter::CalculateMoveLeftRightInput);
}

void AMainPaperCharacter::CalculateMoveLeftRightInput(float Value) 
{
    MovePoint = FVector(Value * MoveSpeedLeftRight * GetWorld()->DeltaTimeSeconds, 0, MovePoint.Z);
}

void AMainPaperCharacter::CalculateMoveUpDownInput(float Value) 
{
    MovePoint = FVector(MovePoint.X, 0, Value * MoveSpeedUpDown * GetWorld()->DeltaTimeSeconds);
}

void AMainPaperCharacter::Move() 
{
    AddActorLocalOffset(MovePoint, true);
}

