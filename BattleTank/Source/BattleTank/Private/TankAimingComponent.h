// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enums for Aiming State
UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked

};


//Forward Declaration
class UTankBarrel; 
class UTankTurret;

// Holds 
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	
	void SetBarrelReference(UTankBarrel * BarrelToSet);

	void SetTurretReference(UTankTurret * TurretToSet);



	void AimAt(FVector HitLocation, float LaunchSpeed);

protected:	
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	EFiringStatus FiringStatus = EFiringStatus::Aiming;

private:

	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;
	


	void MoveBarrelTowards(FVector AimDirection);
};
