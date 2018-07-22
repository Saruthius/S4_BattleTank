// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "Engine/World.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	// Pointer Protection
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

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	// Pointer Protection
	if (!LeftTrack || !RightTrack)
	{
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: One or more of the tracks trying to move does not exist!"), Time)
		return;
	}

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

	// TODO Prevent double speed due to dual control use - fly-by-wire and the individual track controls
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super as we are completely replacing functionality

	auto TankName = GetOwner()->GetName();
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f:\tTank %s \twants to move at velocity \t%s"), Time, *TankName, *MoveVelocity.ToString())
}
