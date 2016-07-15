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
	//No need to call super as we're replacing the functionality

	//Current Forward
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	
	//Direction that tank would like to be heading
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	//Use vector dot product to determine degree of move forward or back.  0 when perp to tank.
	
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);

	IntendMoveForward(ForwardThrow);

	auto RightThrow = FVector::CrossProduct( TankForward, AIForwardIntention).Z;

	IntendTurnRight(RightThrow);


	//UE_LOG(LogTemp, Warning, TEXT("%s Veloctoring to %s"), *TankName, *MoveVelocityString);
}


void UTankMovementComponent::IntendMoveForward(float Throw) {

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	//ToDO prevent double-speed due to dual stick and bumper
}

void UTankMovementComponent::IntendTurnRight(float Throw) {

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

	//ToDO prevent double-speed due to dual stick and bumper
}
