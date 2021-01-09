// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveItemWidget.h"


void UInteractiveItemWidget::SetOwningActor(AActor* NewOwner)
{
	if (OwningActor == NewOwner)
	{
		return;
	}
	OwningActor = NewOwner;

	//OnOwningActorChanged.Broadcast(NewOwner);
}

