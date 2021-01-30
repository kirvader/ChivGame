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
#include "CharacterCameraComponent.h"
#include "InteractableItem.h"
#include "BaseInteractable.h"
#include <algorithm>

namespace {
	ABaseInteractable* GetFirstElement(AMainCharacterPawn* CurrentCharacter) {
		for (auto Element : CurrentCharacter->CurrentInteractableActors)
		{
			return Element;
		}
		return nullptr;
	}
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

	Camera = CreateDefaultSubobject<UCharacterCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);

	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

}

// Called when the game starts or when spawned
void AMainCharacterPawn::BeginPlay()
{
	Super::BeginPlay();

	Camera->UpdateBackgroundSpriteRange();
	RadiansPlaneAngle = (90 - PlaneAngle) * PI / 180.f;
}

void AMainCharacterPawn::OnInteract()
{
}

void AMainCharacterPawn::SwitchItem() 
{
	if (Inventory->CurrentItem == nullptr) return;
	Inventory->SwitchToNextItem();
}

void AMainCharacterPawn::OnPickUpItemCall()
{
	/*if (CurrentInteractiveItem == nullptr) return;
	
	CurrentInteractiveItem->SetActorHiddenInGame(true);

	AInteractableItem* CastedItem = Cast<AInteractableItem>(CurrentInteractiveItem);
	if (CastedItem == nullptr) return;
	
	
	Inventory->AddItem(CastedItem->CastedItemInInventory);*/
}



// Called every frame
void AMainCharacterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateHeroIsMoving();
	MoveHero();
	Camera->MoveTo(HeroSprite->GetComponentLocation());
	Camera->UpdateZoom();
	// UE_LOG(LogTemp, Warning, TEXT("Camera location %f %f %f"), Camera->GetComponentLocation().X, Camera->GetComponentLocation().Y, Camera->GetComponentLocation().Z);
}

// Called to bind functionality to input
void AMainCharacterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("SwitchItem", IE_Pressed, this, &AMainCharacterPawn::SwitchItem);


	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacterPawn::OnInteract);
	PlayerInputComponent->BindAction("PickUpItem", IE_Pressed, this, &AMainCharacterPawn::OnPickUpItemCall);

    PlayerInputComponent->BindAxis("MoveUpAndDown", this, &AMainCharacterPawn::CalculateMoveUpDownInput);
    PlayerInputComponent->BindAxis("MoveLeftAndRight", this, &AMainCharacterPawn::CalculateMoveLeftRightInput);
}


void AMainCharacterPawn::RemoveInteractableActor(ABaseInteractable* ActorRef)
{
	CurrentInteractableActors.Remove(ActorRef);
}

void AMainCharacterPawn::AddInteractableActor(ABaseInteractable* ActorRef)
{
	if (ActorRef == nullptr || ActorRef->IsHidden()) {
		UE_LOG(LogTemp, Warning,
			TEXT("Added action is null or hidden"));
		return;
	}
	UE_LOG(LogTemp, Warning,
		TEXT("Added action is not null"));
	CurrentInteractableActors.Add(ActorRef);
}

void AMainCharacterPawn::InteractTable_Implementation(ABaseInteractable* InteractableThing)
{

}

void AMainCharacterPawn::PickUpItem_Implementation(ABaseInteractable* PickupAbleItem)
{
	
}



void AMainCharacterPawn::CalculateMoveLeftRightInput(float Value) 
{
    HeroMoveDirection = FVector(
		Value * MoveSpeedLeftRight * GetWorld()->DeltaTimeSeconds, 
		HeroMoveDirection.Y, 
		HeroMoveDirection.Z
	);
	
}

void AMainCharacterPawn::CalculateMoveUpDownInput(float Value) 
{
    HeroMoveDirection = FVector(
		HeroMoveDirection.X, 
		-Value * MoveSpeedUpDown * GetWorld()->DeltaTimeSeconds * cos(RadiansPlaneAngle), 
		Value * MoveSpeedUpDown * GetWorld()->DeltaTimeSeconds * sin(RadiansPlaneAngle)
	);
}

void AMainCharacterPawn::MoveHero() {
	Camera->SetFOVStatus(NeedZoom() ? CameraFOV_Zoomed : CameraFOV_Normal);
	HeroSprite->AddWorldOffset(HeroMoveDirection, true);
	
	HeroMoveDirection = FVector(0, 0, 0);
}

void AMainCharacterPawn::UpdateHeroIsMoving() 
{
	PlayerIsMoving = HeroMoveDirection.Size() > 0.1;
	FString str = PlayerIsMoving ? TEXT("true") : TEXT("false");
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("player is moving: %s"), *str));
}

bool AMainCharacterPawn::NeedZoom()
{
	
	FRectangle BackgroundRectangle = Camera->ActualBackgroundRectangle;

	UE_LOG(LogTemp, Warning, TEXT("Highest point: %f"), (3 * BackgroundRectangle.Highest + BackgroundRectangle.Lowest) / 4);
	UE_LOG(LogTemp, Warning, TEXT("Lowest point: %f"), (BackgroundRectangle.Highest + 3 * BackgroundRectangle.Lowest) / 4);
	UE_LOG(LogTemp, Warning, TEXT("Hero is on %f by z"), HeroSprite->GetComponentLocation().Z);
	UE_LOG(LogTemp, Warning, TEXT("____________________________________________________"));


	bool Result = ((HeroSprite->GetComponentLocation().Z <= (3 * BackgroundRectangle.Highest + BackgroundRectangle.Lowest) / 4) &&
		(HeroSprite->GetComponentLocation().Z >= (BackgroundRectangle.Highest + 3 * BackgroundRectangle.Lowest) / 4));
	int ResultInInt = Result ? 1 : 0;

	UE_LOG(LogTemp, Warning, TEXT("Result %d"), ResultInInt);

	return Result;
}

void AMainCharacterPawn::UseItem(UItem *Item) 
{
	if (Item) {
		Item->Use(this);
		Item->OnUse(this);
	}
}
