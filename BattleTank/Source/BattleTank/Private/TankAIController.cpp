// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"

#include "TankAIController.h"


ATank * ATankAIController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank * MyTank = GetControlledTank();
	ATank * PlayerTank = GetPlayerTank();


	if (!MyTank) {

		UE_LOG(LogTemp, Warning, TEXT("AIController - No Tank Found"))
	}
	else {

		UE_LOG(LogTemp, Warning, TEXT("AIController - Possessed: %s"), *MyTank->GetName())
	}


	if (!PlayerTank) {

		UE_LOG(LogTemp, Warning, TEXT("AIController - No Player Tank Found"))
	}
	else {

		UE_LOG(LogTemp, Warning, TEXT("AIController - Player Tank Is: %s"), *PlayerTank->GetName())
	}


}

