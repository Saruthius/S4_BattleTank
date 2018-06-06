// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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
	
	// Weird formatting to adjust for long if statement
	if 
	(
	// Input for above if statement - returns a bool
		UGameplayStatics::SuggestProjectileVelocity
		// Parameters for above function
		(
			this,
			OutLaunchVelocity,	// OUT PARAMETER
			StartLocation,
			HitLocation,
			LaunchSpeed,
			false,				// Ignores the high arc and chooses the low arc
			0,					// TODO Make actual projectile and change this to actual radius
			0,					// Does not override gravity
			ESuggestProjVelocityTraceOption::DoNotTrace
		)
	)
	{
		// Turns the launch velocity vector into a unit vector
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Tank %s is Aiming at %s"), *TankName, *AimDirection.ToString())
	}

	// If we don't find a solution for suggessting the projectile velocity, we do nothing
}