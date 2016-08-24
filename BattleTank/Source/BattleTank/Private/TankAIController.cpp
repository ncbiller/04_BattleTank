// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"

#include "TankAimingComponent.h"
#include "TankAIController.h"
#include "Tank.h"

ATankAIController::ATankAIController() {
	//UE_LOG(LogTemp, Warning, TEXT("%s Constructor Called"), *GetName());
}

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("%s BeginPlay Called"), *GetName());
	
}


void ATankAIController::SetPawn(APawn * InPawn) {
	Super::SetPawn(InPawn);
	//UE_LOG(LogTemp, Warning, TEXT("%s SetPawn Called"), *GetName());
	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}

}

void ATankAIController::OnTankDeath() {
	UE_LOG(LogTemp, Warning, TEXT("%s IsNow Dead"), *GetPawn()->GetName());
	GetPawn()->DetachFromControllerPendingDestroy();

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



