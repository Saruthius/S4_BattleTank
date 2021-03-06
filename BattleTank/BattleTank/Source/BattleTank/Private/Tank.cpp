// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Projectile.h"
#include "Engine/World.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s BANJO: Tank Constructor from Code"), *TankName)
}

void ATank::BeginPlay()
{
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s BANJO: Tank Begin Play from Code"), *TankName)

	// Needed for Blueprint BeginPlay to run
	Super::BeginPlay(); 
}

// Aims at the specified location
void ATank::AimAt(FVector HitLocation)
{
	if (!TankAimingComponent)
	{
		return;
	}
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	bool isReloaded = ((GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds);

	// Pointer protection
	if (Barrel && isReloaded)
	{
		// Spawns in a projectile at the end of the barrel - where the socket for the projectile is
		auto Projectile = GetWorld()->SpawnActor<AProjectile>
		(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
		);

		if (Projectile)
		{
			Projectile->LaunchProjectile(LaunchSpeed);
			LastFireTime = GetWorld()->GetTimeSeconds();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%f: No projectile created!"), GetWorld()->GetTimeSeconds())
		}
	}

	return;
}

