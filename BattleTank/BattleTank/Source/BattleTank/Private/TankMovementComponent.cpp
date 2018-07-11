// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "Engine/World.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet)
	{
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: One or more of the tracks trying to be set does not exist!"), Time)
			return;
	}

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: Intend move forward = %f"), Time, Throw)

	if (!LeftTrack || !RightTrack)
	{
			auto Time = GetWorld()->GetTimeSeconds();
			UE_LOG(LogTemp, Warning, TEXT("%f: One or more of the tracks trying to move does not exist!"), Time)
			return;
	}

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	// TODO Prevent double speed due to dual control use - fly-by-wire and the individual track controls
}


