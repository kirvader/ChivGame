// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


class UItem;
class APickupableItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHIVGAME_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UFUNCTION(BlueprintCallable)
	bool AddItem(APickupableItem* Item);
	UFUNCTION(BlueprintCallable)
	bool RemoveItem(APickupableItem* Item);

	//// ��������, ������� ������ � ������ �� ��������
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Items")
	//TArray<TSubclassOf<APickupableItem> > DefaultItems;
	
	// ����������� ���������
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	int32 Capacity = 5;
	
	// ������� �������� ������. ����� ��� ������� ���������-����������� � ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
	TArray<APickupableItem*> Items;

	UFUNCTION(BlueprintCallable)
	void SwitchToNextItem();
	
	// �������, ������� ����� ������ � �����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
		APickupableItem* CurrentItem = nullptr;

	

protected:

	//// �������, ������� ��������� ��� ��������� �������� � ���������.
	//// ��� ��� ����� ��������� - ��� ���������� ������, �� ��� ������� �������, ��� ������ 1 �������
	//void AddDefaults();

	// Called when the game starts
	virtual void BeginPlay() override;


		
};
