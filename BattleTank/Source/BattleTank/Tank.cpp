// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;	
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();	
}

float ATank::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) {
	


		int32 DamagePoints = FPlatformMath::RoundToInt(Damage);

	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("%s has been damaged by %f damage taken %i, current Health is %i"), *GetName(), Damage,  DamageToApply, CurrentHealth)
	return DamageToApply;
}

// Called every frame
void ATank::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}




