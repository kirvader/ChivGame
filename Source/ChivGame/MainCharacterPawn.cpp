// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterPawn.h"
#include "Camera/CameraComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperSprite.h"
#include "Components/StaticMeshComponent.h"
#include "Sound/SoundCue.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Item.h"
#include "InventoryComponent.h"
#include "BaseInteractiveThing.h"
#include "InteractiveItemWidgetComponent.h"
#include "InteractableItem.h"
#include "BaseInteractable.h"
#include <algorithm>

void AMainCharacterPawn::SetNormalFOV()
{
	TargetCameraFOV = NormalFOV;
}

void AMainCharacterPawn::SetZoomedFOV()
{
	TargetCameraFOV = ZoomedFOV;
}

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


void AMainCharacterPawn::SwitchItem() 
{
	if (Inventory->CurrentItem == nullptr) return;
	Inventory->SwitchToNextItem();
}

void AMainCharacterPawn::OnPickUpItemCall()
{
	
}

void AMainCharacterPawn::CallWidget()
{
	
}

// Called every frame
void AMainCharacterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateHeroIsMoving();
	MoveHero();
	// UE_LOG(LogTemp, Warning, TEXT("Camera location %f %f %f"), Camera->GetComponentLocation().X, Camera->GetComponentLocation().Y, Camera->GetComponentLocation().Z);
}

// Called to bind functionality to input
void AMainCharacterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("SwitchItem", IE_Pressed, this, &AMainCharacterPawn::SwitchItem);

	PlayerInputComponent->BindAction("CallWidget", IE_Pressed, this, &AMainCharacterPawn::CallWidget);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacterPawn::OnDefaultAction);
	PlayerInputComponent->BindAction("PickUpItem", IE_Pressed, this, &AMainCharacterPawn::OnPickUpItemCall);

    PlayerInputComponent->BindAxis("MoveUpAndDown", this, &AMainCharacterPawn::CalculateMoveUpDownInput);
    PlayerInputComponent->BindAxis("MoveLeftAndRight", this, &AMainCharacterPawn::CalculateMoveLeftRightInput);
}


void AMainCharacterPawn::RemoveInteractableActor()
{
	CurrentInteractableActor = nullptr;
}

void AMainCharacterPawn::OnDefaultAction()
{
	if (CurrentInteractableActor == nullptr) return;

	CurrentInteractableActor->DefaultAction(this);
	UpdateActiveItem();
}

void AMainCharacterPawn::SetInteractableActor(ABaseInteractable* ActorRef)
{
	CurrentInteractableActor = ActorRef;
}

void AMainCharacterPawn::InteractTable_Implementation(ABaseInteractable* InteractableThing)
{

}

void AMainCharacterPawn::UpdateActiveItem_Implementation()
{
	
}

void AMainCharacterPawn::CalculateMoveLeftRightInput(float Value) 
{
    HeroMoveDirection = FVector(Value * MoveSpeedLeftRight * GetWorld()->DeltaTimeSeconds, HeroMoveDirection.Y, HeroMoveDirection.Z);
	
}

void AMainCharacterPawn::CalculateMoveUpDownInput(float Value) 
{
    HeroMoveDirection = FVector(HeroMoveDirection.X, -Value * MoveSpeedUpDown * GetWorld()->DeltaTimeSeconds * cos(RadiansPlaneAngle), Value * MoveSpeedUpDown * GetWorld()->DeltaTimeSeconds * sin(RadiansPlaneAngle));
}

void AMainCharacterPawn::MoveHero() {
	HeroSprite->AddWorldOffset(HeroMoveDirection, true);
	HeroMoveDirection = FVector(0, 0, 0);
}

void AMainCharacterPawn::UpdateHeroIsMoving() 
{
	PlayerIsMoving = HeroMoveDirection.Size() > 0.1;
	FString str = PlayerIsMoving ? TEXT("true") : TEXT("false");
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("player is moving: %s"), *str));
}
