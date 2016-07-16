// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:

protected:

	UFUNCTION(BlueprintCallable, Category = "Setup")
		ATank * GetControlledTank() const;

private:

	UPROPERTY(EditDefaultsOnly)
		float CrossHairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
		float CrossHairYLocation = 0.333333;

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000;

	
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
