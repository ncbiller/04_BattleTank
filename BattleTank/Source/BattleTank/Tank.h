// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel; //Forward Declaration


class AProjectile;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	
	//void AimAt(FVector HitLocation);
	
	UFUNCTION(BlueprintCallable, Category = Events)
	void Fire();



protected:


	



private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaTime ) override;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000; //Sensible starting value of 100 m/s

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSecs = 3; 

	double LastFiredTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile>  ProjectileBlueprint; 

	

	//Local Barrel Refrence
	UTankBarrel * Barrel = nullptr;


};
