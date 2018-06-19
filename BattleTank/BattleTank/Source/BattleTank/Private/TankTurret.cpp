// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"


void UTankTurret::Azimate(float RelativeSpeed)
{
	// Just a protection in case Relative speed is too big or too small
	// Needs to be a unit value
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);

	// Move the barrel the right amount this frame
	// Given a max Azimuth speed and a frame time
	auto AzimuthChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewAzimuth = RelativeRotation.Yaw + AzimuthChange;

	// Sets the Azimuth rotation of the turret
	SetRelativeRotation(FRotator(0, NewAzimuth, 0));

	return;
}


