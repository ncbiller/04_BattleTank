// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle) {


	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;

	FVector ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
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
	UE_LOG(LogTemp, Warning, TEXT("Track Hit"));
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{

	//sideways slippage speed is dot product of veloctiy and component RightVector

	auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

	//Acceleration this frame to correct

	auto Acceleration = -(SlippageSpeed / DeltaTime ) * GetRightVector();

	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	auto ForceRequired = (TankRoot->GetMass() * Acceleration) / 2;

	TankRoot->AddForce(ForceRequired);

	//UE_LOG(LogTemp, Warning, TEXT("Slippage Speed %f"), SlippageSpeed);
}
