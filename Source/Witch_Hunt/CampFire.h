// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "CampFire.generated.h"

UCLASS()
class WITCH_HUNT_API ACampFire : public AActor
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this actor's properties
	ACampFire();

public:	


	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* Fire;
	UPROPERTY(EditAnywhere)
		UBoxComponent * MyBoxComponent;
	UPROPERTY(EditAnywhere)
		AActor* MyCharacter;
	UPROPERTY(EditAnywhere)
		FHitResult MyHit;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UDamageType> FireDamageType;

	bool bCanApplyDamage;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent * OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult&SweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		void ApplyFireDamage();
};
