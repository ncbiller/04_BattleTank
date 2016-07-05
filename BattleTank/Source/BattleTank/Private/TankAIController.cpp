// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"


ATank * ATankAIController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank * MyTank = GetControlledTank();

	if (!MyTank) {

		UE_LOG(LogTemp, Warning, TEXT("AIController - No Tank Found"))
	}
	else {

		UE_LOG(LogTemp, Warning, TEXT("AIController - Possessed: %s"), *MyTank->GetName())
	}




}

