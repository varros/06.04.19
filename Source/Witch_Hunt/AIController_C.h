// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Witch.h"
#include "AIController_C.generated.h"

/**
 * 
 */
UCLASS()
class WITCH_HUNT_API AAIController_C : public AAIController
{
	GENERATED_BODY()
	
private:

	virtual void BeginPlay() override;

	AWitch* GetControlledCharacter() const;

	AWitch* GetPlayerCharacter() const;
};
