// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyFollow.generated.h"

UCLASS()
class WITCH_HUNT_API AEnemyFollow : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyFollow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		USceneComponent* Root;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		AActor *goal;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		float speed;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		float accuracy;


};