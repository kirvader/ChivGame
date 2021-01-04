// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterPawn.h"
#include "Camera/CameraComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperSprite.h"
#include "Components/StaticMeshComponent.h"
#include "Sound/SoundCue.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "ChivGame/Item.h"
#include "ChivGame/InventoryComponent.h"
#include<sstream>
#include <ChivGame/InteractableItem.h>

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

	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));


}

// Called when the game starts or when spawned
void AMainCharacterPawn::BeginPlay()
{
	Super::BeginPlay();
	RadiansPlaneAngle = (90 - PlaneAngle) * PI / 180.f;
}

void AMainCharacterPawn::OnInteract() 
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("called Interact")));
	if (CurrentInteractiveActor == nullptr) return; // игрок находится не в зоне взаимодействия
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Interacted on table")));
	InteractTable();
	TargetCameraFOV = NormalFOV + ZoomedFOV - TargetCameraFOV;
}
//void AMainCharacterPawn::SwitchItem() 
//{
//	if (Inventory->CurrentItem == nullptr) return;
//	Inventory->SwitchToNextItem();
//}

void AMainCharacterPawn::OnPickUpItemCall()
{
	if (CurrentInteractiveItem == nullptr) return;
	
	CurrentInteractiveItem->SetActorHiddenInGame(true);

	AInteractableItem* CastedItem = Cast<AInteractableItem>(CurrentInteractiveItem);
	if (CastedItem == nullptr) return;
	
	
	Inventory->AddItem(CastedItem->CastedItemInInventory);
}

// Called every frame
void AMainCharacterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateHeroIsMoving();
	MoveHero();
	CalculateCameraMoveLeftRightInput();
	CalculateCameraFOVAndZoom();
	ZoomCamera();
	MoveCamera();
	// UE_LOG(LogTemp, Warning, TEXT("Camera location %f %f %f"), Camera->GetComponentLocation().X, Camera->GetComponentLocation().Y, Camera->GetComponentLocation().Z);
}

// Called to bind functionality to input
void AMainCharacterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacterPawn::OnInteract);
	PlayerInputComponent->BindAction("PickUpItem", IE_Pressed, this, &AMainCharacterPawn::OnPickUpItemCall);
	
    PlayerInputComponent->BindAxis("MoveUpAndDown", this, &AMainCharacterPawn::CalculateMoveUpDownInput);
    PlayerInputComponent->BindAxis("MoveLeftAndRight", this, &AMainCharacterPawn::CalculateMoveLeftRightInput);
}

void AMainCharacterPawn::SetCurrentInteractiveActor(AActor *ActorRef) 
{
	CurrentInteractiveActor = ActorRef;
	if (CurrentInteractiveActor == nullptr) {
		TargetCameraFOV = NormalFOV;
	}
	// FString str = CurrentInteractiveActor== nullptr ? TEXT("nullptr") : TEXT("good thing");
	
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Current Interactive Actor is : %s"), *str));
}

void AMainCharacterPawn::SetCurrentInteractiveItem(AActor* ActorRef)
{
	CurrentInteractiveItem = ActorRef;
	// FString str = CurrentInteractiveActor== nullptr ? TEXT("nullptr") : TEXT("good thing");

	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Current Interactive Actor is : %s"), *str));
}


void AMainCharacterPawn::InteractTable_Implementation()
{

}

void AMainCharacterPawn::PickUpItem_Implementation()
{

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

void AMainCharacterPawn::CalculateCameraFOVAndZoom() 
{
	if (abs(CurrentCameraFOV - TargetCameraFOV) > 1.f)
		CurrentCameraFOV = CurrentCameraFOV + (TargetCameraFOV - CurrentCameraFOV) * CameraLagFOV;
	// UE_LOG(LogTemp, Warning, TEXT("Camera location %f %f %f"), Camera->GetComponentLocation().X, Camera->GetComponentLocation().Y, Camera->GetComponentLocation().Z);
	if (TargetCameraFOV != ZoomedFOV) {
		FVector CameraCurrentLocation = Camera->GetComponentLocation();
		if (abs(CameraCurrentLocation.Z) < 0.2f) return;
		float ZDirection = CameraCurrentLocation.Z * (1 - CameraLagFOV) - CameraCurrentLocation.Z;
		CameraMovementDirection = FVector(CameraMovementDirection.X, CameraMovementDirection.Y, ZDirection);
		return;
	}
	FVector CameraCurrentLocation = Camera->GetComponentLocation();
	if (CurrentInteractiveActor->GetActorLocation().Z < -300.f) {
		float ZDirection = (-200 - CameraCurrentLocation.Z) * CameraLagFOV;
		CameraMovementDirection = FVector(CameraMovementDirection.X, CameraMovementDirection.Y, ZDirection);
	}
}

void AMainCharacterPawn::ZoomCamera() 
{
	Camera->SetFieldOfView(CurrentCameraFOV);
}

void AMainCharacterPawn::CalculateMoveUpDownInput(float Value) 
{
    HeroMoveDirection = FVector(HeroMoveDirection.X, -Value * MoveSpeedUpDown * GetWorld()->DeltaTimeSeconds * cos(RadiansPlaneAngle), Value * MoveSpeedUpDown * GetWorld()->DeltaTimeSeconds * sin(RadiansPlaneAngle));
}

void AMainCharacterPawn::MoveHero() {
	HeroSprite->AddWorldOffset(HeroMoveDirection, true);
	HeroMoveDirection = FVector(0, 0, 0);
}

void AMainCharacterPawn::MoveCamera() {
	Camera->AddWorldOffset(CameraMovementDirection, true);
	CameraMovementDirection = FVector(0, 0, 0);
}

void AMainCharacterPawn::UpdateHeroIsMoving() 
{
	PlayerIsMoving = HeroMoveDirection.Size() > 0.1;
	FString str = PlayerIsMoving ? TEXT("true") : TEXT("false");
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("player is moving: %s"), *str));
}

void AMainCharacterPawn::UseItem(UItem *Item) 
{
	if (Item) {
		Item->Use(this);
		Item->OnUse(this);
	}
}