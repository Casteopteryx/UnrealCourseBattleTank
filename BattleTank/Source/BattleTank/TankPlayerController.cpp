// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "TankPlayerController.h"


ATankPlayerController::ATankPlayerController()
	: APlayerController()
{
	;
}

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


void ATankPlayerController::Tick(float dt)
{
	AimTowardsCrosshair();
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void  ATankPlayerController::AimTowardsCrosshair()
{
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		GetControlledTank()->AimAt(HitLocation);
		//UE_LOG(LogTemp, Warning, TEXT("aiming towards somewhere"));
	}
	else {
		;
		//UE_LOG(LogTemp, Warning, TEXT("aiming towards the sky"));
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	// look half line
	FVector CameraWorldLocation;
	FVector WorldDirection;
	GetLookInfo(CameraWorldLocation, WorldDirection);

	// Line-trace along the look direction
	FHitResult Hit;
	FVector StartTrace = CameraWorldLocation + MinLineTraceRange * WorldDirection;
	FVector EndTrace = CameraWorldLocation + LineTraceRange * WorldDirection;
	// DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Purple, false, 100.f, ECC_WorldStatic, 1.f);
	// UE_LOG(LogTemp, Warning, TEXT("camera world at %s  camera at %s"), *(CameraWorldLocation.ToString()), *(PlayerCameraManager->GetCameraLocation().ToString()));
	if (GetWorld()->LineTraceSingleByChannel(
		Hit,
		StartTrace,
		EndTrace,
		ECollisionChannel::ECC_Visibility)) {
		;
		UE_LOG(LogTemp, Warning, TEXT("impact at %s"), *(Hit.Location.ToString()));
		HitLocation = Hit.Location;
		// see what we hit
		return true;
	}
	HitLocation = FVector(0.);
	return false;
}

bool ATankPlayerController::GetLookInfo(FVector &CameraWorldLocation, FVector &WorldDirection) const
{
	// find crosshairposition in screen coordinate
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);
	UE_LOG(LogTemp, Warning, TEXT("crosshair at %s"), *(ScreenLocation.ToString()));

	// "de-project" screen position to world position
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, WorldDirection);
}
