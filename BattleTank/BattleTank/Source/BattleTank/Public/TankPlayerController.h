// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ATank * GetControlledTank() const;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	// Start the tank moving the barrel so the shot would hit 
	// where the crosshair intersects the world
	void AimTowardsCrosshair();

private:

	// Returns an OUT PARAMETER of where we hit something, and a bool of if we hit something
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;
	
	ATank * ControlledTank = nullptr;

	// Variables for the location of the crosshair as a percentage of the screen
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333f;

};
