// Fill out your copyright notice in the Description page of Project Settings.

#include "MedKit.h"

// Sets default values
AMedKit::AMedKit()
{
	PrimaryActorTick.bCanEverTick = true;
	OnActorBeginOverlap.AddDynamic(this, &AMedKit::OnOverlap);
}

void AMedKit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));

	NewLocation.Z += DeltaHeight * ZValue;

	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);
}

void AMedKit::OnOverlap(AActor * MyOverlappedActor, AActor * OtherActor)
{
	if (OtherActor != nullptr && OtherActor != this)
	{
		class AWitch* MyCharacter = Cast<AWitch>(OtherActor);

		if (MyCharacter && MyCharacter->GetHealth() < 1.0f)
		{
			MyCharacter->UpdateHealth(100.0f);
			Destroy();
		}
	}
}
