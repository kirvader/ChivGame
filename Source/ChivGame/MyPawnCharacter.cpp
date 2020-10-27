// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawnCharacter.h"

// Sets default values
AMyPawnCharacter::AMyPawnCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPawnCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawnCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawnCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

