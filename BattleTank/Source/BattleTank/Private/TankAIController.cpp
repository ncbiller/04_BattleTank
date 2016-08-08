// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"

#include "TankAimingComponent.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	
	
}


void ATankAIController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	auto MyTank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (MyTank && PlayerTank && AimingComponent) {

		MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius in centrementers

		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		// only fire if locked
		if (AimingComponent->GetFiringState() == EFiringStatus::Locked) {
			AimingComponent->Fire();
		}
		
	}
}



