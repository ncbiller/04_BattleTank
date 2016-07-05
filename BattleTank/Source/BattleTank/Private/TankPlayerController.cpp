// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"





void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank * MyTank = GetControlledTank();

	if (!MyTank) {

		UE_LOG(LogTemp, Warning, TEXT("PlayerController - No Tank Found"))
	}
	else {

		UE_LOG(LogTemp, Warning, TEXT("PlayerController - Possessed: %s"), *MyTank->GetName())
	}




}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();
	
}

ATank * ATankPlayerController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrossHair() {
	if (!GetControlledTank()) { return; }
	
	FVector HitLocation; // Out Parameter
	
	if (GetSightRayHitLocation(HitLocation)) {
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());

	}

	// Get world location via linetracte through crosshair
	// If it hits the landscape
	// Tell controlled tank to aim at this point

	

}

bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation)
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;  // Size of current viewport
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	
	// "De=project the screen position of the crosshair to a world direction
	// line-trace along the look direction and see what we hit (up to max range)
	HitLocation = FVector(ScreenLocation.X, ScreenLocation.Y, 0);


	return true;
}

