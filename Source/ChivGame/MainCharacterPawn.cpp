// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterPawn.h"
#include "Camera/CameraComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperSprite.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMainCharacterPawn::AMainCharacterPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HeroStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));
	RootComponent = HeroStaticMesh;
	HeroStaticMesh->SetSimulatePhysics(true);

	HeroSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("HeroSprite"));
	HeroSprite->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMainCharacterPawn::BeginPlay()
{
	Super::BeginPlay();
	RadiansPlaneAngle = (90 - PlaneAngle) * PI / 180.f;

}

// Called every frame
void AMainCharacterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveHero();
	CalculateCameraMoveLeftRightInput();
	CalculateCameraZoomWhenPlayerIsNear();
	MoveCamera();
}

// Called to bind functionality to input
void AMainCharacterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
    PlayerInputComponent->BindAxis("MoveUpAndDown", this, &AMainCharacterPawn::CalculateMoveUpDownInput);
    PlayerInputComponent->BindAxis("MoveLeftAndRight", this, &AMainCharacterPawn::CalculateMoveLeftRightInput);
}

void AMainCharacterPawn::CalculateCameraMoveLeftRightInput() 
{
	FVector PlayerPawnLocation = HeroSprite->GetComponentLocation();
	FVector CameraCurrentLocation = Camera->GetComponentLocation();
	FVector TargetCameraLocation;
	if (PlayerPawnLocation.X > CameraCurrentLocation.X) {
		TargetCameraLocation = FVector(std::min(PlayerPawnLocation.X, RightestCameraPosition), CameraCurrentLocation.Y, CameraCurrentLocation.Z);
	} else
	{
		TargetCameraLocation = FVector(std::max(PlayerPawnLocation.X, LeftestCameraPosition), CameraCurrentLocation.Y, CameraCurrentLocation.Z);
	}
	CameraMovementDirection = FVector((TargetCameraLocation.X - CameraCurrentLocation.X) * CameraLag, CameraMovementDirection.Y, CameraMovementDirection.Z);
	
}

void AMainCharacterPawn::CalculateMoveLeftRightInput(float Value) 
{
    HeroMoveDirection = FVector(Value * MoveSpeedLeftRight * GetWorld()->DeltaTimeSeconds, HeroMoveDirection.Y, HeroMoveDirection.Z);
	
}
void AMainCharacterPawn::CalculateCameraZoomWhenPlayerIsNear() 
{
	FVector PlayerPawnLocation = HeroSprite->GetComponentLocation();
	FVector CameraCurrentLocation = Camera->GetComponentLocation();
	FVector TargetCameraLocation;
	if (PlayerPawnLocation.Z < ZFourth) {
		TargetCameraLocation = FVector(CameraCurrentLocation.X, ZoomedCameraLinePosition.Y, ZoomedCameraLinePosition.Z);
	} else
	{
		TargetCameraLocation = FVector(CameraCurrentLocation.X, NormalCameraLinePosition.Y, NormalCameraLinePosition.Z);
	}
	CameraMovementDirection = FVector(CameraMovementDirection.X, (TargetCameraLocation.Y - CameraCurrentLocation.Y) * CameraLag, (TargetCameraLocation.Z - CameraCurrentLocation.Z) * CameraLag);
	UE_LOG(LogTemp, Warning, TEXT("Camera direction %f %f"), TargetCameraLocation.X, TargetCameraLocation.Y, TargetCameraLocation.Z);
}
void AMainCharacterPawn::CalculateMoveUpDownInput(float Value) 
{
    HeroMoveDirection = FVector(HeroMoveDirection.X, -Value * MoveSpeedUpDown * GetWorld()->DeltaTimeSeconds * cos(RadiansPlaneAngle), Value * MoveSpeedUpDown * GetWorld()->DeltaTimeSeconds * sin(RadiansPlaneAngle));
}

void AMainCharacterPawn::MoveHero() {
	HeroSprite->AddWorldOffset(HeroMoveDirection, true);
}

void AMainCharacterPawn::MoveCamera() {
	Camera->AddWorldOffset(CameraMovementDirection, true);
}