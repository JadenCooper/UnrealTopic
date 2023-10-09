// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	UE_LOG(LogTemp, Display, TEXT("Configured Moved Distance: %f"), MoveDistance);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();

	CurrentLocation += PlatformVelocity * DeltaTime;

	SetActorLocation(CurrentLocation);

	float DistanceTraveled = FVector::Dist(StartLocation, CurrentLocation);

	if(DistanceTraveled > MoveDistance)
	{
		float Overshoot = DistanceTraveled - MoveDistance;
		UE_LOG(LogTemp, Display, TEXT("Overshot By: %f"), Overshoot);

		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation += MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);
	    PlatformVelocity = -PlatformVelocity;
	}
}

