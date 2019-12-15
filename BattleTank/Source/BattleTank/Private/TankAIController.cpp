// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("ATankAIController BeginPlay"))

	auto myToy = GetControlledTank();
	if (myToy) {
		FString tankName = myToy->GetName();
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController BeginPlay with %s"), *tankName)
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController BeginPlay but no toy"))
	}

	auto myEnemy = GetPlayerTank();
	if (myEnemy) {
		FString tankName = myEnemy->GetName();
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController BeginPlay aiming at %s"), *tankName)
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController BeginPlay but nothing to destroy"))
	}
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto world = GetWorld();
	if (world == nullptr) { UE_LOG(LogTemp, Error, TEXT("World is not here")); return NULL; }
	auto controller = world->GetFirstPlayerController();
	if (controller == nullptr) { UE_LOG(LogTemp, Error, TEXT("No one controls anything here")); return NULL; }
	ATankPlayerController * tankController = Cast<ATankPlayerController>(controller);
	if (tankController == nullptr) { UE_LOG(LogTemp, Error, TEXT("Who is this fool in control")); return NULL; }
	auto target = tankController->GetControlledTank();
	if (target == nullptr) { UE_LOG(LogTemp, Error, TEXT("What is he doing")); return NULL; }
	return target;
}
