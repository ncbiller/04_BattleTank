// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"



ATank * ATankPlayerController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank * MyTank = GetControlledTank();

	if (!MyTank) {

		UE_LOG(LogTemp, Warning, TEXT("PlayerController - No Tank Found"))
	}
	else {

		UE_LOG(LogTemp, Warning, TEXT("PlayerController - Possessed: %s"), *MyTank->GetName())
	}




}
