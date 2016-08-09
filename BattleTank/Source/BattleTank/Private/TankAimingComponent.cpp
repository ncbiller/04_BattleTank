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

	



	if (isReloaded) {

		if (IsBarrelMoving()) {
			FiringStatus = EFiringStatus::Aiming;
		}
		else {
			FiringStatus = EFiringStatus::Locked;
		}
	}

	if (AmmoRemaining <= 0) { 
		FiringStatus = EFiringStatus::AmmoOut; 
	}
}

bool UTankAimingComponent::IsBarrelMoving() {

	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01); // vectors are equa
}


void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return FiringStatus;
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
		AimDirection = LaunchVelocity.GetSafeNormal();
		
		
		MoveBarrelTowards(AimDirection);
		
	}




}

int32 UTankAimingComponent::GetRoundsRemaining() const
{
	return AmmoRemaining;
}

void UTankAimingComponent::Fire() {
	if (!ensure(Barrel)) { return; }

	if (!ensure(ProjectileBlueprint)) { return; }

	//if (!(ensure(Barrel) && ensure(ProjectileBlueprint))) { return; }

	if ((FiringStatus == EFiringStatus::Locked) || (FiringStatus == EFiringStatus::Aiming)) {

		//Spawn Projectile at Barrel Location
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetForwardVector().Rotation(), FActorSpawnParameters());
		
		AmmoRemaining--;


		Projectile->LaunchProjectile(LaunchSpeed);
		LastFiredTime = FPlatformTime::Seconds();
	}
}




void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	//Convert Aim Derection into Rotator (pitch and yaw) should be no roll

	if (!ensure(Barrel) || !ensure(Turret)) { return; }

	
	auto RotationQuaternion = FQuat::FindBetweenVectors(Barrel->GetForwardVector(), AimDirection);
	

	
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();

	DeltaRotator = AimAsRotator - BarrelRotator;
	
	
	//Use Quaternion to sort Yaw rotation. Will always take shortest path
	Turret->Rotate(RotationQuaternion.Rotator().Yaw);



	//Quaternion doesn't work for some reason so use simple subtraction.  Works as always within 90 degrees
	Barrel->Elevate(DeltaRotator.Pitch); 
	

}



