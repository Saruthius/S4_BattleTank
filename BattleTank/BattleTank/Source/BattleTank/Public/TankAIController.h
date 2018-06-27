// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/// Forward Declarations
class ATank;


UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:

	// Outdated Getters that are not needed
	/*
	ATank * GetControlledTank() const;
	ATank * GetPlayerTank() const;
	*/

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	ATank * ControlledTank = nullptr;	
	ATank * PlayerTank = nullptr;
};
