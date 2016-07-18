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
class AProjectile;
class UTankAimingComponent;

// Holds 
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	




	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet);

	void AimAt(FVector HitLocation);


	UFUNCTION(BlueprintCallable, Category = Events)
	void Fire();

protected:	
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000; //Sensible starting value of 100 m/s

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSecs = 3;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile>  ProjectileBlueprint;

private:


	
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;


	void MoveBarrelTowards(FVector AimDirection);

	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;

	double LastFiredTime = 0;

	bool isReloaded;

	FRotator DeltaBarrelRotator;
	FRotator DeltaTurretRotator;

};
