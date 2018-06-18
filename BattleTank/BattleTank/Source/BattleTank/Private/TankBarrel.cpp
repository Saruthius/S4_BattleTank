// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Just a protection in case Relative speed is too big or too small
	// Needs to be a unit value
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);

	// Move the barrel the right amount this frame
	// Given a max elevation speed and a frame time
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	// Clamps Elevation to the declared mins and maxes
	auto ClampedElevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	
	// Sets the elevation rotation of the barrel
	SetRelativeRotation(FRotator(ClampedElevation, 0, 0));
}


