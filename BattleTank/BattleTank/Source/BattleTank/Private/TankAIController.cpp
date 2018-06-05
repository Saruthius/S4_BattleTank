// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


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
		if (!PlayerPawn)
		{
			UE_LOG(LogTemp, Error, TEXT("No Player Tank can be found by %s!"), *(ControlledTank->GetName()))
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AI Controlled Tank named %s found player tank named %s"), *(ControlledTank->GetName()), *(PlayerTank->GetName()))
		}
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