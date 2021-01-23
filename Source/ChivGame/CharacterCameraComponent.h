// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "CharacterCameraComponent.generated.h"

/**
 * 
 */
class UTexture2D;
UENUM()
enum CameraZoomStatus
{
	CameraFOV_Normal	UMETA(DisplayName = "Stopped"),
	CameraFOV_Zoomed	UMETA(DisplayName = "Moving"),
};

UCLASS()
class CHIVGAME_API UCharacterCameraComponent : public UCameraComponent
{
	GENERATED_BODY()

public:
	void MoveTo(FVector TargetPosition);

	void UpdateZoom();

	// Коэффициент задержки движения камеры
	// Для того чтобы камера не сразу ехала за игроком, а с небольшой задержкой
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float CameraLag = 0.6f;

	// Приближенный угол обзора камеры(когда игрок взаимодействует)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float ZoomedFOV = 70.f;

	// Нормальный угол обзора камеры (Задается в эдиторе)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float NormalFOV = 90.f;

	// Коэффициент задержки приближения камеры (Задается в эдиторе)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float CameraLagFOV = 0.07f;

	// Ссылка нужна для получения ее размеров
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
		UTexture2D* BackgroundImage;

	
	void SetFOVStatus(CameraZoomStatus Status);

protected:
	virtual void BeginPlay() override;

private:
	/// <summary>
	///
	/// Пусть есть нормаль к плоскости задника, тогда введем еще 1 плоскость, пересекающую героя и перпендикулярную этой нормали
	/// 
	/// </summary>
	/// <returns>
	/// 
	///	Если теперь получить ортогональную проекцию камеры на получившуюся плоскость, то можно будет вычислить смещение от текущего положения камеры до нужного.
	/// # Здесь должна быть ссылка на конфлюенс #
	///  
	/// </returns>
	FVector GetAxisOffset(FVector TargetPosition);

	CameraZoomStatus CurrentFOVStatus = CameraFOV_Normal;

	float TargetFOV = 90.f;

	float GetNextMomentFOV();

	float ActualBackgroundWidth = 0.f;
	float ActualBackgroundHeight = 0.f;

};
