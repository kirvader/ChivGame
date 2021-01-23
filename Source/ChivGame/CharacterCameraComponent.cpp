// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCameraComponent.h"
#include "PaperSpriteActor.h"

#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

void UCharacterCameraComponent::SetFOVStatus(CameraZoomStatus Status)
{
	CurrentFOVStatus = Status;
	switch (CurrentFOVStatus)
	{
		case CameraFOV_Normal:
			TargetFOV = NormalFOV;
		case CameraFOV_Zoomed:
			TargetFOV = ZoomedFOV;
	}
}

void UCharacterCameraComponent::BeginPlay()
{
	Super::BeginPlay();
	
	
	// getting background sprite scale
	TArray<AActor*> BackgroundSpriteActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APaperSpriteActor::StaticClass(), BackgroundSpriteActors);
	for (AActor* actor : BackgroundSpriteActors) {
		APaperSpriteActor* Casted = Cast<APaperSpriteActor>(actor);
		FVector BackgroundScale = Casted->GetActorScale();
		ActualBackgroundWidth = BackgroundScale.X * BackgroundImage->GetSurfaceWidth();
		ActualBackgroundHeight = BackgroundScale.Z * BackgroundImage->GetSurfaceHeight();
	}

}

// TargetPosition should be in World space
FVector UCharacterCameraComponent::GetAxisOffset(FVector TargetPosition)
{
	FVector CurrentPosition = GetComponentLocation();

	FVector PositionOffset = (TargetPosition - CurrentPosition) * CameraLag;
	PositionOffset.Y = 0.0;

	return PositionOffset;
}

float UCharacterCameraComponent::GetNextMomentFOV()
{
	return FieldOfView + (TargetFOV - FieldOfView) * CameraLagFOV;
}

void UCharacterCameraComponent::MoveTo(FVector TargetPosition) {
	AddWorldOffset(GetAxisOffset(TargetPosition), true);
}

void UCharacterCameraComponent::UpdateZoom()
{
	SetFieldOfView(GetNextMomentFOV());
}
