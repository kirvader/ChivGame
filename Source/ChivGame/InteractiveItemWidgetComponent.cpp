// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveItemWidgetComponent.h"
#include "InteractiveItemWidget.h"

UInteractiveItemWidgetComponent::UInteractiveItemWidgetComponent() 
{
	SetWidgetSpace(EWidgetSpace::Screen);
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UInteractiveItemWidgetComponent::InitWidget() 
{
	Super::InitWidget();
	if (Widget)
	{
		UInteractiveItemWidget* WidgetInst = Cast<UInteractiveItemWidget>(Widget);
		if (WidgetInst)
		{
			WidgetInst->SetOwningActor(GetOwner());
		}
	}
}

FVector UInteractiveItemWidgetComponent::GetRelativeVector()
{
	return FVector(x, y, z);
}
