// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
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





void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {

	auto OurTankName = GetOwner()->GetName();
	if (!Barrel) {
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
		//,ESuggestProjVelocityTraceOption::TraceFullPath
	);

	float Time = GetWorld()->GetTimeSeconds();
		
	if (bLaunchSuccess) {
		auto AimDirection = LaunchVelocity.GetSafeNormal();
		
		
		MoveBarrelTowards(AimDirection);
		
	}




}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	//Convert Aim Derection into Rotator (pitch and yaw) should be no roll

	//apply yaw component to turret at given rate per frame
	auto AimAsRotator = AimDirection.Rotation();
	
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto DeltaBarrelRotator = AimAsRotator - BarrelRotator;

	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto DeltaTurretRotator = AimAsRotator - TurretRotator;

	Barrel->Elevate(DeltaBarrelRotator.Pitch); 
	Turret->Rotate(DeltaTurretRotator.Yaw);
	auto OurTankName = GetOwner()->GetName();
	float Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("Frame Time: %f - %s firing in rotation %f"), Time, *OurTankName, DeltaTurretRotator.Yaw)
}


