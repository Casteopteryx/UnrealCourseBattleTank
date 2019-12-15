// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("ATankAIController BeginPlay"))
}

void ATankAIController::Tick(float dt)
{
	Super::Tick(dt);
	auto myToy = GetControlledTank();
	auto myEnemy = GetPlayerTank();
	if (myToy && myEnemy) {
		myToy->AimAt(myEnemy->GetActorLocation());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Something is missing"))
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
