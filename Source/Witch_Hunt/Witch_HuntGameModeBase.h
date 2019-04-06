// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Witch.h"
#include "Witch_HuntGameModeBase.generated.h"

/**
 * 
 */

UENUM()
enum class EGamePlayState
{
	EPlaying,
	EGameOver,
	EUnknown
};
UCLASS()
class WITCH_HUNT_API AWitch_HuntGameModeBase : public AGameModeBase
{
	GENERATED_BODY()



	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	AWitch * MyCharacter;

	UFUNCTION(Blueprintpure, Category = "Health")
		EGamePlayState GetCurrentState() const;

	void SetCurrentState(EGamePlayState NewState);

private:
	EGamePlayState CurrentState;

	void HandleNewState(EGamePlayState NewState);

};
