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

	// ����������� �������� �������� ������
	// ��� ���� ����� ������ �� ����� ����� �� �������, � � ��������� ���������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float CameraLag = 0.6f;

	// ������������ ���� ������ ������(����� ����� ���������������)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float ZoomedFOV = 70.f;

	// ���������� ���� ������ ������ (�������� � �������)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float NormalFOV = 90.f;

	// ����������� �������� ����������� ������ (�������� � �������)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float CameraLagFOV = 0.07f;

	// ������ ����� ��� ��������� �� ��������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
		UTexture2D* BackgroundImage;

	
	void SetFOVStatus(CameraZoomStatus Status);

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

	float TargetFOV = 90.f;

	float GetNextMomentFOV();

	float ActualBackgroundWidth = 0.f;
	float ActualBackgroundHeight = 0.f;

};
