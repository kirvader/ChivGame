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

USTRUCT(BlueprintType)
struct FRectangle
{
	GENERATED_USTRUCT_BODY()
	// X coord
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
		float Leftest = 0.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
		float Rightest = 0.0;
	// Z coord
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
		float Lowest = 0.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
		float Highest = 0.0;

	FRectangle() {
		Leftest = 0.0;
		Rightest = 0.0;
		Lowest = 0.0;
		Highest = 0.0;
	}

	FRectangle(float Center_X, float Center_Z, float Width, float Height) {
		Leftest = Center_X - Width / 2;
		Rightest = Center_X + Width / 2;
		Lowest = Center_Z - Height / 2;
		Highest = Center_Z + Height / 2;
	}
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


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		int CameraPrototypeID = 1;

	// Приближенный угол обзора камеры(когда игрок взаимодействует)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float ZoomedFOV = 70.f;

	// Нормальный угол обзора камеры (Задается в эдиторе)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float NormalFOV = 90.f;

	// Коэффициент задержки приближения камеры к взаимодействию (Задается в эдиторе)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float CameraLagFOV = 0.07f;
	
	// Коэффициент приближения камеры при движении камеры вверх-вниз
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float CameraDirectionPlaneAngle = 20.f;

	// Ссылка нужна для получения ее размеров
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
		UTexture2D* BackgroundImage;

	FRectangle ActualBackgroundRectangle;
	
	void SetFOVStatus(CameraZoomStatus Status);
	
	void UpdateBackgroundSpriteRange();

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
	
	FVector2D GetGameResolution();

	float TargetFOV = 90.f;

	float GetNextMomentFOV();


	float ActualBackgroundWidth = 0.f;
	float ActualBackgroundHeight = 0.f;

	FVector ActualBackGroundCenter = FVector(0.f, 0.f, 0.f);

	void UpdateCurrentShowingRectangle();

	FRectangle CurrentShowingPlaneRectangle;

	float Max(float value1, float value2);
	float Min(float value1, float value2);

};


