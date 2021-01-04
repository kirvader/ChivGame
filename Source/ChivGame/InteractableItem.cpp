// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableItem.h"
#include <Paper2D/Classes/PaperSpriteComponent.h>
#include "ChivGame/MainCharacterPawn.h"
#include <ChivGame/Item.h>
#include "Components/BoxComponent.h"

// Sets default values
AInteractableItem::AInteractableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("Root Component"));

	ItemSprite = CreateDefaultSubobject<UPaperSpriteComponent>(FName("Item Sprite"));
	ItemSprite->SetupAttachment(RootComponent);
	SetupShapeComponent();

}

void AInteractableItem::SetupShapeComponent()
{
	// Create the trigger subobject and set it up
	auto BoxTrigger = CreateDefaultSubobject<UBoxComponent>(FName("Trigger Shape"));
	BoxTrigger->SetBoxExtent(FVector(50.f, 50.f, 20.f));
	BoxTrigger->SetGenerateOverlapEvents(true);
	BoxTrigger->SetupAttachment(ItemSprite);
	TriggerShape = BoxTrigger;
}

void AInteractableItem::BindTriggerCallbacksToTriggerShape()
{
	if (TriggerShape)
	{
		// Workaround. Prevents cached constructors to add delegates twice.
		TriggerShape->OnComponentBeginOverlap.RemoveDynamic(
			this, &AInteractableItem::OnTriggerOverlapBegin);
		TriggerShape->OnComponentEndOverlap.RemoveDynamic(
			this, &AInteractableItem::OnTriggerOverlapEnd);

		TriggerShape->OnComponentBeginOverlap.AddDynamic(this, &AInteractableItem::OnTriggerOverlapBegin);
		TriggerShape->OnComponentEndOverlap.AddDynamic(this, &AInteractableItem::OnTriggerOverlapEnd);
	}
}

void AInteractableItem::OnTriggerOverlapBegin
(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
) {
	// Prevent self collision and check if only collision
	// to specific actor is wanted.
	if (OtherActor &&
		(OtherActor != this) &&
		(OtherActor == ActorThatTriggers ||
			ActorThatTriggers == nullptr))
	{
		AMainCharacterPawn* CastedActor = Cast<AMainCharacterPawn>(OtherActor);
		if (!CastedActor) return;
		CastedActor->SetCurrentInteractiveItem(this);
		TriggerOverlapBeginEvent.Broadcast();
		TriggerCallbackOn();
	}
}

void AInteractableItem::OnTriggerOverlapEnd
(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex
) {
	// Prevent self collision and check if only collision
	// to specific actor is wanted.
	if (OtherActor &&
		(OtherActor != this) &&
		(OtherActor == ActorThatTriggers ||
			ActorThatTriggers == nullptr))
	{
		AMainCharacterPawn* CastedActor = Cast<AMainCharacterPawn>(OtherActor);
		if (!CastedActor) return;
		CastedActor->SetCurrentInteractiveItem(nullptr);
		TriggerOverlapEndEvent.Broadcast();
		TriggerCallbackOff();
	}
}

void AInteractableItem::TriggerCallbackOn_Implementation() {}

void AInteractableItem::TriggerCallbackOff()
{
	UE_LOG(LogTemp, Warning,
		TEXT("SimpleTriggerVolume::TriggerCallbackOff(). To add functionality, override this function."));
}


// Called when the game starts or when spawned
void AInteractableItem::BeginPlay()
{
	Super::BeginPlay();
	CastedItemInInventory = NewObject<UItem>(ItemInInventory, ItemInInventory->GetFName(), RF_NoFlags, ItemInInventory.GetDefaultObject());
	BindTriggerCallbacksToTriggerShape();
}

// Called every frame
void AInteractableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

