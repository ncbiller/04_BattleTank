// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"



void UTankTurret::Rotate(float RelativeSpeed) {

	if (RelativeSpeed > 180) { RelativeSpeed = 180 - RelativeSpeed; }
	if (RelativeSpeed < -180) { RelativeSpeed = -180 - RelativeSpeed; }


	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f);
	//Apply pitch component to barrell at a given rate per frame
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;



	SetRelativeRotation(FRotator(0, RawNewRotation, 0));

}
