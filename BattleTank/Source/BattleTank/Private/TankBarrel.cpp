// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed) {
	
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f);
	//Apply pitch component to barrell at a given rate per frame
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	SetRelativeRotation(FRotator(FMath::Clamp(RawNewElevation,MinElevationDegrees,MaxElevationDegrees), 0, 0));

}

