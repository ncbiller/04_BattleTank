// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
 // Holds Turret properties and components
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//-1 to +1 to move at MaxSpeed clockwise AntiClockwise
	void Rotate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesPerSecond = 25;


	
};
