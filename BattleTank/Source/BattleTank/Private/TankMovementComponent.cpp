// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	UE_LOG(LogTemp, Warning, TEXT("Request Move Velocty : %s"), *MoveVelocity.ToString());
}


void UTankMovementComponent::IntendMoveForward(float Throw) {

	//auto Name = GetName();
	//auto Time = GetWorld()->GetTimeSeconds();

	

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	//ToDO prevent double-speed due to dual stick and bumper
}

void UTankMovementComponent::IntendTurnRight(float Throw) {

	//auto Name = GetName();
	//auto Time = GetWorld()->GetTimeSeconds();


	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

	//ToDO prevent double-speed due to dual stick and bumper
}
