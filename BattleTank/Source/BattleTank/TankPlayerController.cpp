// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController BeginPlay"))

	auto myToy = GetControlledTank();
	if (myToy) {
		FString tankName = myToy->GetName();
		UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController BeginPlay with %s"), *tankName)
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController BeginPlay but no toy"))
	}
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
