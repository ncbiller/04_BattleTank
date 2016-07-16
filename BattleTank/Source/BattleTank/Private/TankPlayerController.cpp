// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"





void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();



	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent) {
		FoundAimingComponent(AimingComponent);
	}
	else {
		UE_LOG(LogTemp,Warning, TEXT("Player Controller can't find aiming component at Begin Play"))
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
		GetControlledTank()->AimAt(HitLocation);

	}

	// Get world location via linetracte through crosshair
	// If it hits the landscape
	// Tell controlled tank to aim at this point

	

}

bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation)
{
	FVector2D ScreenLocation;
	
	GetScreenLocation(ScreenLocation);
	
	FVector LookDirection, WorldPosition;
	if (GetLookDirection(ScreenLocation,WorldPosition, LookDirection)) {
		
		// line-trace along the look direction and see what we hit (up to max range)

		HitLocation = FVector(1);

		if (GetLookVectorHitLocation(HitLocation, WorldPosition, LookDirection)
		) {return true;}
	}


	
	


	return false;
}

void ATankPlayerController::GetScreenLocation(FVector2D &ScreenLocation)
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;  // Size of current viewport
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
}


// "De=project the screen position of the crosshair to a world direction
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & WorldPosition, FVector & LookDirection)
{
	
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldPosition, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector & HitLocation,FVector & WorldPosition, FVector & LookDirection) {

	FHitResult OutHit;
	FVector Start = WorldPosition;
	FVector End = Start + LookDirection * LineTraceRange;
	ECollisionChannel TraceChannel = ECollisionChannel::ECC_Visibility;
	FCollisionQueryParams Params = FCollisionQueryParams
	(
		FName(),
		false,
		GetControlledTank()
	);

	FCollisionResponseParams ResponseParam = FCollisionResponseParams(ECollisionResponse::ECR_Block);

	HitLocation = FVector(1);

	if (GetWorld()->LineTraceSingleByChannel
	(
		OutHit,
		Start,
		End,
		TraceChannel
	)
		) {
		HitLocation = OutHit.Location;
		return true;
	}

	return false;
}