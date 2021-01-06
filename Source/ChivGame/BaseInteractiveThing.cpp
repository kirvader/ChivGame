// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInteractiveThing.h"
#include "Components/BoxComponent.h"
#include "ChivGame/MainCharacterPawn.h"
#include "InteractiveItemWidgetComponent.h"
#include "PaperSpriteComponent.h"


// Sets default values
ABaseInteractiveThing::ABaseInteractiveThing()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a separate root component, so the 
	// trigger volume may be placed relatively
	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("Root Component"));
	SetupShapeComponent();
	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>(FName("Sprite"));
	Sprite->SetupAttachment(RootComponent);

	Widget = CreateDefaultSubobject<UInteractiveItemWidgetComponent>(FName("Widget"));
	Widget->SetupAttachment(RootComponent);
	Widget->SetVisibility(false);
	Widget->SetRelativeLocation(Widget->GetRelativeVector());
}

void ABaseInteractiveThing::SetupShapeComponent() 
{
	// Create the trigger subobject and set it up
	auto BoxTrigger = CreateDefaultSubobject<UBoxComponent>(FName("Trigger Shape"));
	BoxTrigger->SetBoxExtent(TriggerExtent);
	BoxTrigger->SetGenerateOverlapEvents(true);
	Shape = BoxTrigger;
}

void ABaseInteractiveThing::BindTriggerCallbacksToShape() 
{
	if (Shape)
	{
		// Workaround. Prevents cached constructors to add delegates twice.
		Shape->OnComponentBeginOverlap.RemoveDynamic(
			this, &ABaseInteractiveThing::OnTriggerOverlapBegin);
		Shape->OnComponentEndOverlap.RemoveDynamic(
			this, &ABaseInteractiveThing::OnTriggerOverlapEnd);

		Shape->OnComponentBeginOverlap.AddDynamic(this, &ABaseInteractiveThing::OnTriggerOverlapBegin);
		Shape->OnComponentEndOverlap.AddDynamic(this, &ABaseInteractiveThing::OnTriggerOverlapEnd);
	}
}

void ABaseInteractiveThing::OnTriggerOverlapBegin
(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult
){
	// Prevent self collision and check if only collision
	// to specific actor is wanted.
	if (OtherActor && 
		(OtherActor != this) && 
		(OtherActor == ActorThatTriggers || 
		ActorThatTriggers == nullptr))
	{
		Widget->SetVisibility(true);
		AMainCharacterPawn *CastedActor = Cast<AMainCharacterPawn>(OtherActor);
		CastedActor->SetCurrentInteractiveActor(this);
		TriggerOverlapBeginEvent.Broadcast();
		TriggerCallbackOn();
	}
}

void ABaseInteractiveThing::OnTriggerOverlapEnd
(
  UPrimitiveComponent* OverlappedComp, 
  AActor* OtherActor, 
  UPrimitiveComponent* OtherComp, 
  int32 OtherBodyIndex
){
	// Prevent self collision and check if only collision
	// to specific actor is wanted.
	if (OtherActor && 
		(OtherActor != this) && 
		(OtherActor == ActorThatTriggers || 
		ActorThatTriggers == nullptr))
	{
		Widget->SetVisibility(false);
		AMainCharacterPawn *CastedActor = Cast<AMainCharacterPawn>(OtherActor);
		CastedActor->SetCurrentInteractiveActor(nullptr);
		TriggerOverlapEndEvent.Broadcast();
		TriggerCallbackOff();
	}
}

void ABaseInteractiveThing::TriggerCallbackOn_Implementation(){}

void ABaseInteractiveThing::TriggerCallbackOff()
{
	UE_LOG(LogTemp, Warning, 
	TEXT("SimpleTriggerVolume::TriggerCallbackOff(). To add functionality, override this function."));
}


// Called when the game starts or when spawned
void ABaseInteractiveThing::BeginPlay()
{
	Super::BeginPlay();
	BindTriggerCallbacksToShape();
}

// Called every frame
void ABaseInteractiveThing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

