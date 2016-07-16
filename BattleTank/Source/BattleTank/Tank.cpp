// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "Private/TankAimingComponent.h"
#include "Private/TankMovementComponent.h"
#include "Private/TankBarrel.h"
#include "Private/TankTurret.h"
#include "Private/Projectile.h"
#include "Tank.h"





void ATank::Fire() {
	bool isReloaded = (FPlatformTime::Seconds() - LastFiredTime) > ReloadTimeInSecs;

	if (Barrel && isReloaded) {

		//Spawn Projectile at Barrel Location
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetForwardVector().Rotation(), FActorSpawnParameters());


		Projectile->LaunchProjectile(LaunchSpeed);
		LastFiredTime = FPlatformTime::Seconds();
	}
}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	

	
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

	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}