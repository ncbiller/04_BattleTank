// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Private/TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UStaticMeshComponent * BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UStaticMeshComponent * TurretToSet);

protected:

	UTankAimingComponent * TankAimingComponent = nullptr;


private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaTime ) override;

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 10000; //Sensible starting value of 100 m/s




};
