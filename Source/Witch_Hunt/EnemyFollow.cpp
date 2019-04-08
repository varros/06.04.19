// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyFollow.h"
#include "Components/StaticMeshComponent.h"
#include "Classes/Kismet/KismetMathLibrary.h"

// Sets default values
AEnemyFollow::AEnemyFollow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(Root);

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

	FVector enemy_location = GetActorLocation();

	FRotator lookAt = UKismetMathLibrary::FindLookAtRotation(
		enemy_location, goal_location
	);

	SetActorRotation(lookAt);

	FVector direction = goal_location - enemy_location;

	SetActorLocation(
		GetActorLocation() + direction.GetUnsafeNormal() * speed * DeltaTime); 

}

