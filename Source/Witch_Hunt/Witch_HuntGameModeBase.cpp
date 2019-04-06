// Fill out your copyright notice in the Description page of Project Settings.

#include "Witch_HuntGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void AWitch_HuntGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SetCurrentState(EGamePlayState::EPlaying);

	MyCharacter = Cast<AWitch>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AWitch_HuntGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MyCharacter)
	{
		if (FMath::IsNearlyZero(MyCharacter->GetHealth(), 0.00f))
		{
			SetCurrentState(EGamePlayState::EGameOver);
		}
	}
}

EGamePlayState AWitch_HuntGameModeBase::GetCurrentState() const
{
	return CurrentState;
}

void AWitch_HuntGameModeBase::SetCurrentState(EGamePlayState NewState)
{
	CurrentState = NewState;
	HandleNewState(CurrentState);
}

void AWitch_HuntGameModeBase::HandleNewState(EGamePlayState NewState)
{
	switch (NewState)
	{
	case EGamePlayState::EPlaying:
	{

	} break;
	case EGamePlayState::EGameOver:
	{
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	} break;
	default:
	case EGamePlayState::EUnknown:
	{

	} break;
	}
}
