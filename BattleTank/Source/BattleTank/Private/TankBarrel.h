// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
// Holds barrel properties and components
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//-1 to +1 to move at MaxSpeed Down or Up
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 10;
	
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees = 40;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegrees = 0;


};
