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

	// ����������� �������� �������� ������
	// ��� ���� ����� ������ �� ����� ����� �� �������, � � ��������� ���������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float CameraLag = 0.6f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		int CameraPrototypeID = 1;

	// ������������ ���� ������ ������(����� ����� ���������������)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float ZoomedFOV = 70.f;

	// ���������� ���� ������ ������ (�������� � �������)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float NormalFOV = 90.f;

	// ����������� �������� ����������� ������ � �������������� (�������� � �������)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float CameraLagFOV = 0.07f;
	
	// ����������� ����������� ������ ��� �������� ������ �����-����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float CameraDirectionPlaneAngle = 20.f;

	// ������ ����� ��� ��������� �� ��������
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
	/// ����� ���� ������� � ��������� �������, ����� ������ ��� 1 ���������, ������������ ����� � ���������������� ���� �������
	/// 
	/// </summary>
	/// <returns>
	/// 
	///	���� ������ �������� ������������� �������� ������ �� ������������ ���������, �� ����� ����� ��������� �������� �� �������� ��������� ������ �� �������.
	/// # ����� ������ ���� ������ �� ��������� #
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


