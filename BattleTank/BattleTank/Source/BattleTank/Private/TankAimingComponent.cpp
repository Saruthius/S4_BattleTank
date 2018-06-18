// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false; // TODO Should this Tick?
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel)
	{
		return;
	}

	// Parameters needed for function call to find where to aim barrel
	FVector OutLaunchVelocity; // OUT PARAMETER - Launch velocity from barrel to end point
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	
	// Direction for the barrel to shoot for the projectile to hit the crosshair - 
	// This is the end result of everything here, for the most part
	FVector AimDirection; 

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,	// OUT PARAMETER
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,				// Default Value
		0,					// Default Value
		0,					// Default Value
		ESuggestProjVelocityTraceOption::DoNotTrace			// Default Value - parameter must be present to avoid bug
	);
	
	if (bHaveAimSolution)
	{
		// Turns the launch velocity vector into a unit vector
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Barrel->Elevate() called at speed %f"), Time, 5.0f)
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: No Solution Found"), Time)
	}
	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) 
{
	// Work out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	// Move the barrel the right amount this frame
	// Given a max elevation speed and a frame time

	Barrel->Elevate(5.0f); //TODO remove magic number
	return;
}