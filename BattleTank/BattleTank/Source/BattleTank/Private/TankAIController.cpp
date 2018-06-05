// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("No Tank is being controlled by this AI!"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled Tank by AI controller = %s"), *(ControlledTank->GetName()))
	}
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

