// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCameraComponent.h"
#include "PaperSpriteActor.h"
#include "Math/UnrealMathUtility.h"

#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

float UCharacterCameraComponent::Max(float value1, float value2)
{
	return value1 > value2 ? value1 : value2;
}

float UCharacterCameraComponent::Min(float value1, float value2)
{
	return value1 < value2 ? value1 : value2;
}
void UCharacterCameraComponent::SetFOVStatus(CameraZoomStatus Status)
{
	CurrentFOVStatus = Status;
	if (CurrentFOVStatus == CameraFOV_Normal) TargetFOV = NormalFOV;
	if (CurrentFOVStatus == CameraFOV_Zoomed) TargetFOV = ZoomedFOV;
}

void UCharacterCameraComponent::BeginPlay()
{
	Super::BeginPlay();
	
	
	// getting background sprite scale
	TArray<AActor*> BackgroundSpriteActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APaperSpriteActor::StaticClass(), BackgroundSpriteActors);
	for (AActor* actor : BackgroundSpriteActors) {
		APaperSpriteActor* Casted = Cast<APaperSpriteActor>(actor);

		if (!Casted) continue;
		FVector BackgroundScale = Casted->GetActorScale();
		
		ActualBackgroundWidth = BackgroundScale.X * BackgroundImage->GetSurfaceWidth();
		ActualBackgroundHeight = BackgroundScale.Z * BackgroundImage->GetSurfaceHeight();
		ActualBackGroundCenter = Casted->GetActorLocation();
	}

	// UE_LOG(LogTemp, Warning, TEXT("width - %f, height - %f"), ActualBackgroundWidth, ActualBackgroundHeight);
	// UE_LOG(LogTemp, Warning, TEXT("Background center location is (%f, %f, %f)"), ActualBackGroundCenter.X, ActualBackGroundCenter.Y, ActualBackGroundCenter.Z);

}

FVector2D UCharacterCameraComponent::GetGameResolution()
{
	FVector2D Result = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());

	// UE_LOG(LogTemp, Warning, TEXT("Resolution is %fx%f"), Result.X, Result.Y);
	return Result;
}

// TargetPosition should be in World space
FVector UCharacterCameraComponent::GetAxisOffset(FVector TargetPosition)
{
	FVector CurrentPosition = GetComponentLocation();

	FVector PositionOffset = (TargetPosition - CurrentPosition) * CameraLag;
	if (CameraPrototypeID >= 2)
		PositionOffset.Y = 0.f;
	else
		PositionOffset.Y = PositionOffset.Z * cos(CameraDirectionPlaneAngle * acos(-1) / 180.f);

	return PositionOffset;
}

float UCharacterCameraComponent::GetNextMomentFOV()
{
	//UE_LOG(LogTemp, Warning, TEXT("Next moment FOV is %f"), FieldOfView + (TargetFOV - FieldOfView) * CameraLagFOV);
	return FieldOfView + (TargetFOV - FieldOfView) * CameraLagFOV;
}


void UCharacterCameraComponent::UpdateCurrentShowingRectangle()
{
	FVector CurrentCameraLocation = GetComponentLocation();

	float CameraPlaneDistance = abs(CurrentCameraLocation.Y - ActualBackGroundCenter.Y);
	float CurrentFOV = FieldOfView;
	float RectangleWidth = 2 * CameraPlaneDistance * tan(CurrentFOV / 2 * acos(-1) / 180.f);

	FVector2D CurrentResolution = GetGameResolution();
	float RectangleHeight = RectangleWidth * CurrentResolution.Y / CurrentResolution.X;

	CurrentShowingPlaneRectangle = FRectangle(CurrentCameraLocation.X, CurrentCameraLocation.Z, RectangleWidth, RectangleHeight);
}

void UCharacterCameraComponent::UpdateBackgroundSpriteRange()
{
	ActualBackgroundRectangle = FRectangle(ActualBackGroundCenter.X, ActualBackGroundCenter.Z, ActualBackgroundWidth, ActualBackgroundHeight);
}

void UCharacterCameraComponent::MoveTo(FVector TargetPosition) {
	
	// проверяем если мы и так за пределами задника
	// такое может быть только в том случае, если по оси, по которой идет несоответствие, симметричный отступ
	// Если же такое не происходит то мы должны это исправить
	// ограничваем вектор перемещения в ином случае и если он выходит за границы дозволенного экрану

	UpdateCurrentShowingRectangle();
	float BackgroundWidth = abs(ActualBackgroundRectangle.Rightest - ActualBackgroundRectangle.Leftest);
	float ShowingWidth = abs(CurrentShowingPlaneRectangle.Rightest - CurrentShowingPlaneRectangle.Leftest);
	float BackgroundHeight = abs(ActualBackgroundRectangle.Highest - ActualBackgroundRectangle.Lowest);
	float ShowingHeight = abs(CurrentShowingPlaneRectangle.Highest - CurrentShowingPlaneRectangle.Lowest);

	/*UE_LOG(LogTemp, Warning, TEXT("background is %f %f"), BackgroundWidth, BackgroundHeight);*/
	// UE_LOG(LogTemp, Warning, TEXT("Showing is %f %f"), ShowingWidth, ShowingHeight);
	// по оси X(горизонталь)
	if (BackgroundWidth <= ShowingWidth) {
		// Если по горизонтали размер задника таков, что может поместиться в камеру с запасом
		TargetPosition.X = ActualBackGroundCenter.X;
	}
	else {
		TargetPosition.X = Max(TargetPosition.X, ActualBackgroundRectangle.Leftest + ShowingWidth / 2);
		TargetPosition.X = Min(TargetPosition.X, ActualBackgroundRectangle.Rightest - ShowingWidth / 2);
	}

	// по оси Z (вертикаль)
	if (BackgroundHeight <= ShowingHeight) {
		// Если по вертикали размер задника таков, что может поместиться в камеру с запасом
		TargetPosition.Z = ActualBackGroundCenter.Z;
	}
	else {
		TargetPosition.Z = Max(TargetPosition.Z, ActualBackgroundRectangle.Lowest + ShowingHeight / 2);
		TargetPosition.Z = Min(TargetPosition.Z, ActualBackgroundRectangle.Highest - ShowingHeight / 2);
	}
	UE_LOG(LogTemp, Error, TEXT("In camera component"));
	UE_LOG(LogTemp, Warning, TEXT("Camera location should be %f %f %f"), TargetPosition.X, TargetPosition.Y, TargetPosition.Z);
	UE_LOG(LogTemp, Warning, TEXT("Camera location will change by %f %f %f"), GetAxisOffset(TargetPosition).X, GetAxisOffset(TargetPosition).Y, GetAxisOffset(TargetPosition).Z);

	AddWorldOffset(GetAxisOffset(TargetPosition), true);
	


}

void UCharacterCameraComponent::UpdateZoom()
{
	SetFieldOfView(GetNextMomentFOV());
}
