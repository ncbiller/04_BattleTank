// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "TankBarrel.h"
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




void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{

	Barrel = BarrelToSet;
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
		ESuggestProjVelocityTraceOption::DoNotTrace
	);


		
	if (bLaunchSuccess) {
		auto AimDirection = LaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("%s firing in direction %s"), *OurTankName, *AimDirection.ToString())
		
		MoveBarrelTowards(AimDirection);
		
	}



}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	//Convert Aim Derection into Rotator (pitch and yaw) should be no roll
	Barrel->Elevate(5); //TODO remove magic number
	//apply yaw component to turret at given rate per frame
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;



}


