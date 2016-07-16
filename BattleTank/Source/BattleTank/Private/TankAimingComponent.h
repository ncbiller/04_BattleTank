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
class UTankAimingComponent;

// Holds 
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();



	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet);

	void AimAt(FVector HitLocation);

protected:	
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	EFiringStatus FiringStatus = EFiringStatus::Aiming;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000; //Sensible starting value of 100 m/s

private:

	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;
	


	void MoveBarrelTowards(FVector AimDirection);
};
