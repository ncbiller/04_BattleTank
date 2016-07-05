// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:


private:

	UPROPERTY(EditAnyWhere)
		float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnyWhere)
		float CrossHairYLocation = 0.333333;

	UPROPERTY(EditAnyWhere)
		float LineTraceRange = 1000000;


	ATank * GetControlledTank() const;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// Start the tank moving the barrel so that a shot would hit where
	// the crosshair intersects the world
	void AimTowardsCrossHair();

	bool GetSightRayHitLocation(FVector & HitLocation);
	void GetScreenLocation(FVector2D &ScreenLocation);
	bool GetLookDirection(FVector2D ScreenLocation, FVector & WorldPosition, FVector & LookDirection);
	bool GetLookVectorHitLocation(FVector & HitLocation, FVector & WorldPosition, FVector & LookDirection);
};
