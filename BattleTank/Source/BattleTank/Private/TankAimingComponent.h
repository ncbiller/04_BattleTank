// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	
	void SetBarrelReference(UStaticMeshComponent * BarrelToSet);

	void SetTurretReference(UStaticMeshComponent * TurretToSet);



	void AimAt(FVector HitLocation, float LaunchSpeed);

	

private:

	UStaticMeshComponent * Barrel = nullptr;
	UStaticMeshComponent * Turret = nullptr;
	
	void MoveBarrelTowards(FVector AimDirection);
};
