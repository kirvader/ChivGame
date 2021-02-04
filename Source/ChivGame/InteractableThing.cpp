// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableThing.h"

AInteractableThing::AInteractableThing() {
	
}

void AInteractableThing::DefaultAction(AMainCharacterPawn* ActingPlayer)
{
	// this should be a custom action for all of these things

	InteractiveAction();
}

void AInteractableThing::InteractiveAction_Implementation()
{

}
