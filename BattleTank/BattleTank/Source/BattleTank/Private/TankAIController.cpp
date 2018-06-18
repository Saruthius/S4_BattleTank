// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = GetControlledTank();
	PlayerTank = GetPlayerTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("No Tank is being controlled by this AI!"))
	}
	else
	{
		if (!PlayerTank)
		{
			UE_LOG(LogTemp, Error, TEXT("No Player Tank can be found by %s!"), *(ControlledTank->GetName()))
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AI Controlled Tank named %s found player tank named %s"), *(ControlledTank->GetName()), *(PlayerTank->GetName()))
		}
	}

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Pointer Protection - Only aims at a player when there is both
	// a controlled tank and a player tank
	if (ControlledTank && PlayerTank)
	{
		// TODO Move Towards the player

		// Aims at the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		// Fire if ready
	}

}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}