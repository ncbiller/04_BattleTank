// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle) {

	MyThrottle = Throttle;


	

}

UTankTrack::UTankTrack()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

}

void UTankTrack::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	//UE_LOG(LogTemp, Warning, TEXT("Track Hit %f"), MyThrottle);

	//sideways slippage speed is dot product of veloctiy and component RightVector

	ApplySlippageForce();

	//UE_LOG(LogTemp, Warning, TEXT("Slippage Speed %f"), SlippageSpeed);
	ApplyTrackForce();
}

void UTankTrack::ApplySlippageForce()
{
	auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

	//Acceleration this frame to correct

	auto DeltaTime = GetWorld()->GetDeltaSeconds();

	auto Acceleration = -(SlippageSpeed / DeltaTime) * GetRightVector();

	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	auto ForceRequired = (TankRoot->GetMass() * Acceleration) / 2;

	TankRoot->AddForce(ForceRequired);
}

void UTankTrack::ApplyTrackForce()
{

	FVector ForceApplied = GetForwardVector() * MyThrottle * TrackMaxDrivingForce;

	FVector ForceLocation = GetComponentLocation();

	auto TankRoot2 = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot2->AddForceAtLocation(ForceApplied, ForceLocation);
}


