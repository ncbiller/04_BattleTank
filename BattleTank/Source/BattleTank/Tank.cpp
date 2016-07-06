// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "Private/TankAimingComponent.h"
#include "Private/TankBarrel.h"
#include "Private/TankTurret.h"
#include "Private/Projectile.h"
#include "Tank.h"


void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret * TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}


void ATank::Fire() {
	if (!Barrel) { return; }

	//Spawn Projectile at Barrel Location
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, 
		Barrel->GetSocketLocation(FName("Projectile")), 
		Barrel->GetForwardVector().Rotation(), FActorSpawnParameters());
	

	Projectile->LaunchProjectile(LaunchSpeed);
}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	//No need to protect pointers as added at construction

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}






void ATank::AimAt(FVector HitLocation) {

	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}