// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATankPlayerController();

	virtual void BeginPlay() override;

	virtual void Tick(float dt) override;

	ATank * GetControlledTank() const;

	void AimTowardsCrosshair();


private:
	bool GetSightRayHitLocation(FVector &HitLocation) const;
	bool GetLookInfo(FVector &CameraWorldLocation, FVector &WorldDirection) const;
	bool GetLookVectorHitLocation(FVector CameraWorldLocation, FVector WorldDirection, FVector &HitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.3;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;

	UPROPERTY(EditAnywhere)
	float MinLineTraceRange = 500.f;
};
