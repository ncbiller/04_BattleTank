// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward(float Throw);
	
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = Input)
	void TriggerRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = Input)
	void TriggerLeft(float Throw);


	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);



private:
	//Called from the pathfinding logic by the AI controllers
	
	UTankMovementComponent(); 

	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
	
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;



	UTankTrack * LeftTrack = nullptr;
	UTankTrack * RightTrack = nullptr;

	float TriggerLeftThrow = 0;
	float TriggerRightThrow = 0;

	float StickForward = 0;
	float StickRight = 0;

};
