// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true; // TODO Should This really tick

	// ...
}

void UTankAimingComponent::BeginPlay() {
	Super::BeginPlay();
	LastFiredTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FiringStatus = EFiringStatus::Reloading;
	isReloaded = (FPlatformTime::Seconds() - LastFiredTime) > ReloadTimeInSecs;

	

	
	//pull out offset info from turret/barrel steering if both pitch and yaw offset are small then cool.

	float Delta = FMath::Abs(DeltaTurretRotator.Yaw) + FMath::Abs(DeltaBarrelRotator.Pitch);

	if (isReloaded) {

		if (Delta > 0.01) {
			FiringStatus = EFiringStatus::Aiming;
		}
		else {
			FiringStatus = EFiringStatus::Locked;
		}
	}

}


void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation) {

	auto OurTankName = GetOwner()->GetName();
	if (!ensure(Barrel)) {
		return;
	}

		
	FVector LaunchVelocity;
	bool bLaunchSuccess;

	bLaunchSuccess = UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocity,
		Barrel->GetSocketLocation(FName("Projectile")),
		HitLocation,
		LaunchSpeed,
		false,
		0.0f,
		0.0f
		,ESuggestProjVelocityTraceOption::DoNotTrace
	);

	float Time = GetWorld()->GetTimeSeconds();
		
	if (bLaunchSuccess) {
		auto AimDirection = LaunchVelocity.GetSafeNormal();
		
		
		MoveBarrelTowards(AimDirection);
		
	}




}

void UTankAimingComponent::Fire() {
	

	if (!ensure(Barrel && ProjectileBlueprint)) { return; }

	if (isReloaded) {

		//Spawn Projectile at Barrel Location
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetForwardVector().Rotation(), FActorSpawnParameters());


		Projectile->LaunchProjectile(LaunchSpeed);
		LastFiredTime = FPlatformTime::Seconds();
	}
}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	//Convert Aim Derection into Rotator (pitch and yaw) should be no roll

	if (!ensure(Barrel) || !ensure(Turret)) { return; }

	//apply yaw component to turret at given rate per frame
	auto AimAsRotator = AimDirection.Rotation();
	
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	
	DeltaBarrelRotator = AimAsRotator - BarrelRotator;

	auto TurretRotator = Turret->GetForwardVector().Rotation();
	
	DeltaTurretRotator = AimAsRotator - TurretRotator;

	

	Barrel->Elevate(DeltaBarrelRotator.Pitch); 
	Turret->Rotate(DeltaTurretRotator.Yaw);
	auto OurTankName = GetOwner()->GetName();
	float Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("Frame Time: %f - %s firing in rotation %f"), Time, *OurTankName, DeltaTurretRotator.Yaw)
}



