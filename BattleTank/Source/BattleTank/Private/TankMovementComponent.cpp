// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"



UTankMovementComponent::UTankMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true; // TODO Should This really tick

											  // ...
}

void UTankMovementComponent::BeginPlay() {
	Super::BeginPlay();
}

void UTankMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	

	LeftTrack->SetThrottle(FMath::Clamp(StickForward + StickRight + TriggerLeftThrow,-1.0f,1.0f));
	RightTrack->SetThrottle(FMath::Clamp(StickForward - StickRight + TriggerRightThrow, -1.0f, 1.0f));
}


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



	StickForward = Throw;

}

void UTankMovementComponent::IntendTurnRight(float Throw) {


	StickRight = Throw;


}

void UTankMovementComponent::TriggerRight(float Throw)
{
	TriggerRightThrow = Throw;
}

void UTankMovementComponent::TriggerLeft(float Throw)
{
	TriggerLeftThrow = Throw;
}
