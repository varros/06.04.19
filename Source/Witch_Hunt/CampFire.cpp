// Fill out your copyright notice in the Description page of Project Settings.

#include "CampFire.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACampFire::ACampFire()
{
	MyBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBoxComponent"));
	MyBoxComponent->InitBoxExtent(FVector(50.f, 50.f, 50.f));
	RootComponent = MyBoxComponent;

	Fire = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("My Fire"));
	Fire->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	Fire->SetupAttachment(RootComponent);

	MyBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACampFire::OnOverlapBegin);
	MyBoxComponent->OnComponentEndOverlap.AddDynamic(this, &ACampFire::OnOverlapEnd);

	bCanApplyDamage = false;

}

void ACampFire::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		bCanApplyDamage = true;
		MyCharacter = Cast<AActor>(OtherActor);
		MyHit = SweepResult;
	}
}

void ACampFire::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	bCanApplyDamage = false;
}


void ACampFire::ApplyFireDamage()
{
	if (bCanApplyDamage)
	{
		UGameplayStatics::ApplyPointDamage(MyCharacter, 200.f, GetActorLocation(), MyHit, nullptr, this, FireDamageType);
	}
}

