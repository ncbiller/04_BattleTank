// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//No need to protect pointers as added at construction

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	
	InputComponent->BindAction("Turret_Clockwise", IE_Pressed, this, &ATank::RotateTurretClockwise);
	//Turret_CounterClockwise
	InputComponent->BindAction("Turret_CounterClockwise", IE_Pressed, this, &ATank::RotateTurretCounterClockwise);
}

void ATank::SetTurretChildActor(UChildActorComponent * TurretFromBP)
{
	Turret = TurretFromBP;
	UE_LOG(LogTemp, Warning, TEXT("SetTurretChildActor Called"));
}

void ATank::RotateTurretClockwise() {
	UE_LOG(LogTemp, Warning, TEXT("RotateTurretClockwise() Called"));
	Turret->SetRelativeRotation(FRotator(0, 30.f, 0));

}

void ATank::RotateTurretCounterClockwise()
{
	UE_LOG(LogTemp, Warning, TEXT("RotateTurretCounterClockwise() Called"));
	Turret->SetRelativeRotation(FRotator(0, -30.f, 0));

}

void ATank::AimAt(FVector HitLocation) {

	TankAimingComponent->AimAt(HitLocation);
}