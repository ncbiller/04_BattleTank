// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"






void ATankAIController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	ATank * MyTank = Cast<ATank>(GetPawn());
	ATank * PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (MyTank && PlayerTank) {

		MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius in centrementers

		MyTank->AimAt(PlayerTank->GetActorLocation());
		MyTank->Fire();
	}
}



