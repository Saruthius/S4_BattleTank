// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("No Tank is being controlled!"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled Tank = %s"), *(ControlledTank->GetName()))
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	// Ensures we have a controlled Tank - pointer protection
	if (!ControlledTank)
	{
		return;
	}

	// OUT PARAMETER
	FVector HitLocation;
	// Checks both if we hit something and changes Hit Location to where we hit something
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Location : %s"), *HitLocation.ToString())	
		

		// TODO Tell controlled tank to aim at this point
	}


}

// Gets the location of linetrace through crosshair, true if it hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	/*
	MY ATTEMPT


	// OUT PARAMETER for what we hit through the raycast
	FHitResult Hit;

	// OUT PARAMETERS for the start of the raycast
	FVector ViewLocation;
	FRotator ViewRotation;

	// Return value for if we hit something
	bool GetHit = false;

	// Sets the view out parameters
	GetPlayerViewPoint(ViewLocation, ViewRotation);

	// Raycast through crosshair
	GetHit = GetWorld()->LineTraceSingleByChannel
	(
		Hit, // OUT PARAMETER
		ViewLocation,
		ViewLocation * (10000, 10000, 10000),
		ECollisionChannel::ECC_Visibility
	);

	// If we Hit something
	if (GetHit)
	{
		// Sets Hitlocation to where we hit something with the linetrace
		OutHitLocation = Hit.ImpactPoint;
	}
	// Returns whether or not we hit something with the linetrace
	return GetHit;
	
	*/

	/// Find Crosshair position
	// OUT PARAMETERS for viewport size
	int32 ViewportSizeX = 0, ViewportSizeY = 0;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	// Gets the location of the crosshair on the screen
	FVector2D ScreenLocation = {ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation};
	UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString())

	// "De-project" screen position of crosshair to a world direction
	// Linetrace along that world direction
	// See what we hit up to max range	
	return true;
}