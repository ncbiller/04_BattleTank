// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:
	

protected:
	// How close can the AI tank get
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float AcceptanceRadius = 10000;
private:

	UFUNCTION()
		void OnTankDeath();

	ATankAIController();

	virtual void BeginPlay() override;

	virtual void SetPawn(APawn * InPawn) override;

	
	
	virtual void Tick(float DeltaTime) override;


};
