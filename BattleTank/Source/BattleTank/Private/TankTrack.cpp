// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle) {

	auto Name = GetName();

	UE_LOG(LogTemp, Warning,TEXT("%s - with value : %f"),*Name, Throttle)
		//TODO Clamp throttle value between 0 and 1
}


