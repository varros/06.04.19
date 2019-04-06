// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "FallingTree.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFall);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WITCH_HUNT_API UFallingTree : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Sets default values for this component's properties
	UFallingTree();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(Blueprintassignable)
		FOnFall FOnFall;

private:
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	AActor* ActorThatFalls = nullptr;
};
