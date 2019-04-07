// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyFollow.h"

// Sets default values
AEnemyFollow::AEnemyFollow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyFollow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyFollow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector goal_location = goal->GetActorLocation();

	FVector pet_location = GetActorLocation();

	FRotator lookAt = UKismetMathLibrary::FindLookAtRotation(
		pet_location, goal_location
	);

	SetActorRotation(lookAt);

	FVector direction = goal_location - pet_location;

	SetActorLocation(
		GetActorLocation() +
		direction.GetUnsafeNormal() * speed * DeltaTime
	);

}

