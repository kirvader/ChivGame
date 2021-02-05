
// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInteractable.h"
#include <Paper2D/Classes/PaperSpriteComponent.h>
#include "ChivGame/MainCharacterPawn.h"
#include <ChivGame/Item.h>
#include "Components/BoxComponent.h"
#include "InteractiveItemWidgetComponent.h"

// Sets default values
ABaseInteractable::ABaseInteractable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("Root Component"));

	ItemSprite = CreateDefaultSubobject<UPaperSpriteComponent>(FName("Item Sprite"));
	ItemSprite->SetupAttachment(RootComponent);
	SetupShapeComponent();

	//Widget = CreateDefaultSubobject<UInteractiveItemWidgetComponent>(FName("Widget"));
	//Widget->SetupAttachment(ItemSprite);
	//Widget->SetVisibility(false);
	//Widget->SetRelativeLocation(Widget->GetRelativeVector());

}

void ABaseInteractable::SetupShapeComponent()
{
	// Create the trigger subobject and set it up
	auto BoxTrigger = CreateDefaultSubobject<UBoxComponent>(FName("Trigger Shape"));
	BoxTrigger->SetBoxExtent(FVector(50.f, 50.f, 20.f));
	BoxTrigger->SetGenerateOverlapEvents(true);
	BoxTrigger->SetupAttachment(ItemSprite);
	TriggerShape = BoxTrigger;
}

void ABaseInteractable::BindTriggerCallbacksToTriggerShape()
{
	if (TriggerShape)
	{
		// Workaround. Prevents cached constructors to add delegates twice.
		TriggerShape->OnComponentBeginOverlap.RemoveDynamic(
			this, &ABaseInteractable::OnTriggerOverlapBegin);
		TriggerShape->OnComponentEndOverlap.RemoveDynamic(
			this, &ABaseInteractable::OnTriggerOverlapEnd);

		TriggerShape->OnComponentBeginOverlap.AddDynamic(this, &ABaseInteractable::OnTriggerOverlapBegin);
		TriggerShape->OnComponentEndOverlap.AddDynamic(this, &ABaseInteractable::OnTriggerOverlapEnd);
	}
}

void ABaseInteractable::OnTriggerOverlapBegin
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

		//ItemSprite->SetMaterial(0, ShimmeryMaterial);
		//Widget->SetVisibility(true);
		//UE_LOG(LogTemp, Warning,
		//	TEXT("Item should had been added"));

		CastedActor->SetInteractableActor(this);
		TriggerOverlapBeginEvent.Broadcast();
		TriggerCallbackOn();
	}
}

void ABaseInteractable::OnTriggerOverlapEnd
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
		
		CastedActor->RemoveInteractableActor();
		ItemSprite->SetMaterial(0, NULL);

		//Widget->SetVisibility(false);
		//CastedActor->SetNormalFOV();
		
		TriggerOverlapEndEvent.Broadcast();
		TriggerCallbackOff();
	}
}

void ABaseInteractable::TriggerCallbackOn_Implementation() {}

void ABaseInteractable::TriggerCallbackOff()
{
	UE_LOG(LogTemp, Warning,
		TEXT("SimpleTriggerVolume::TriggerCallbackOff(). To add functionality, override this function."));
}

void ABaseInteractable::DefaultAction(AMainCharacterPawn* ActingPlayer)
{
}


// Called when the game starts or when spawned
void ABaseInteractable::BeginPlay()
{
	Super::BeginPlay();
	BindTriggerCallbacksToTriggerShape();
}

