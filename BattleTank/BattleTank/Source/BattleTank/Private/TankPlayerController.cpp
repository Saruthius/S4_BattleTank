// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"

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
		ControlledTank->AimAt(HitLocation);
	}


}

// Gets the location of linetrace through crosshair, true if it hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{

	/// Find Crosshair position in pixel coordinates
	// OUT PARAMETERS for viewport size
	int32 ViewportSizeX = 0, ViewportSizeY = 0;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	// Gets the location of the crosshair on the screen
	FVector2D ScreenLocation = {ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation};

	// OUT PARAMETERS for the deprojection
	FVector LookDirection;

	// "De-project" screen position of crosshair to a world direction
	if (GetLookDirection(ScreenLocation, LookDirection))
	{	
		// Linetrace along that world direction, and returns whether or not we hit something
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld
	(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		OutLookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	// Hit result for the linetrace
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		OutHitLocation = HitResult.Location;
		return true;
	}

	OutHitLocation = FVector (0.0);
	return false;

}