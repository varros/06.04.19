// Fill out your copyright notice in the Description page of Project Settings.

#include "AIController_C.h"
#include "Engine/World.h"
#include "Witch.h"

void AAIController_C::BeginPlay() {
	Super::BeginPlay();
}

AWitch * AAIController_C::GetControlledCharacter() const
{
	return Cast<AWitch>(GetCharacter());
	
}

AWitch * AAIController_C::GetPlayerCharacter() const
{
	auto PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerCharacter) { return nullptr; }
	return Cast<AWitch>(PlayerCharacter);
}
