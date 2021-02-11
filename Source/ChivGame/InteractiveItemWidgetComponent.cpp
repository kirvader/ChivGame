// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveItemWidgetComponent.h"
#include "InteractiveItemWidget.h"
#include "BaseInteractable.h"

UInteractiveItemWidgetComponent::UInteractiveItemWidgetComponent() 
{
	SetWidgetSpace(EWidgetSpace::Screen);
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

