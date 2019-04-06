// Fill out your copyright notice in the Description page of Project Settings.

#include "Witch.h"

#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Projectile.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "TimerManager.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Components/TimelineComponent.h"


// Sets default values
AWitch::AWitch()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true;
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false;

	// Create a camera
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;

}

// Called when the game starts or when spawned
void AWitch::BeginPlay()
{
	Super::BeginPlay();

	FullHealth = 1000.0f;
	Health = FullHealth;
	HealthPercentage = 1.0f;
	bCanBeDamaged = true;

	FullMagic = 100.0f;
	Magic = FullMagic;
	MagicPercentage = 1.0f;
	PreviousMagic = MagicPercentage;
	MagicValue = 0.0f;
	bCanUseMagic = true;

	if (MagicCurve)
	{
		FOnTimelineFloat TimelineCallback;
		FOnTimelineEventStatic TimelineFinishedCallback;

		TimelineCallback.BindUFunction(this, FName("SetMagicValue"));
		TimelineFinishedCallback.BindUFunction(this, FName("SetMagicState"));

		MyTimeline = NewObject<UTimelineComponent>(this, FName("Magic Animation"));
		MyTimeline->AddInterpFloat(MagicCurve, TimelineCallback);
		MyTimeline->SetTimelineFinishedFunc(TimelineFinishedCallback);
		MyTimeline->RegisterComponent();
	}
}

// Called every frame
void AWitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MyTimeline != nullptr) MyTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, nullptr);
}

// Called to bind functionality to input
void AWitch::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AWitch::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AWitch::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AWitch::Jump);
	PlayerInputComponent->BindAction("StopJumping", IE_Released, this, &AWitch::StopJumping);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AWitch::Fire);

}

void AWitch::MoveForward(float value)
{
	if ((Controller != NULL) && (value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}

void AWitch::MoveRight(float value)
{
	if ((Controller != NULL) && (value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, value);
	}
}

void AWitch::Jump()
{
	bPressedJump = true;
}

void AWitch::StopJump()
{
	bPressedJump = false;
}


void AWitch::Fire()
{
	// try and fire a projectile
	if (ProjectileClass != NULL && !FMath::IsNearlyZero(Magic, 0.001f) && bCanUseMagic)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			
				const FRotator SpawnRotation = GetControlRotation();
				// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
				const FVector SpawnLocation = ((Magic_PointLocation != nullptr) ? Magic_PointLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(MagicOffset);

				//Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				// spawn the projectile at the muzzle
				World->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}

		// try and play the sound if specified
		if (FireSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}


		if (MyTimeline != nullptr) MyTimeline->Stop();
		GetWorldTimerManager().ClearTimer(MagicTimerHandle);
		SetMagicChange(-20.0f);
		GetWorldTimerManager().SetTimer(MagicTimerHandle, this, &AWitch::UpdateMagic, 5.0f, false);
	}
}

float AWitch::GetHealth()
{
	return HealthPercentage;
}

float AWitch::GetMagic()
{
	return MagicPercentage;
}

FText AWitch::GetHealthIntText()
{
	int32 HP = FMath::RoundHalfFromZero(HealthPercentage * 100);
	FString HPS = FString::FromInt(HP);
	FString HealthHUD = HPS + FString(TEXT("%"));
	FText HPText = FText::FromString(HealthHUD);
	return HPText;
}

FText AWitch::GetMagicIntText()
{
	int32 MP = FMath::RoundHalfFromZero(MagicPercentage * 100);
	FString MPS = FString::FromInt(MP);
	FString FullMPS = FString::FromInt(FullMagic);
	FString MagicHUD = MPS + FString(TEXT("/")) + FullMPS;
	FText MPText = FText::FromString(MagicHUD);
	return MPText;
}

void AWitch::SetDamageState()
{
	bCanBeDamaged = true;
}

void AWitch::DamageTimer()
{
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AWitch::SetDamageState, 2.0f, false);
}

void AWitch::SetMagicValue()
{
	TimelineValue = MyTimeline->GetPlaybackPosition();
	CurveFloatValue = PreviousMagic + MagicValue * MagicCurve->GetFloatValue(TimelineValue);
	Magic = FMath::Clamp(CurveFloatValue*FullHealth, 0.0f, FullMagic);
	MagicPercentage = FMath::Clamp(CurveFloatValue, 0.0f, 1.0f);
}

void AWitch::SetMagicState()
{
	bCanUseMagic = true;
	MagicValue = 0.0;
	if (GunDefaultMaterial) Magic_Point->SetMaterial(0, GunDefaultMaterial);
}

bool AWitch::PlayFlash()
{
	if (redFlash)
	{
		redFlash = false;
		return true;
	}

	return false;
}


void AWitch::UpdateHealth(float HealthChange)
{
	Health = FMath::Clamp(Health += HealthChange, 0.0f, FullHealth);
	HealthPercentage = Health / FullHealth;
}

void AWitch::ReceivePointDamage(float Damage, const UDamageType * DamageType, FVector HitLocation, FVector HitNormal, UPrimitiveComponent * HitComponent, FName BoneName, FVector ShotFromDirection, AController * InstigatedBy, AActor * DamageCauser, const FHitResult & HitInfo)
{
	bCanBeDamaged = false;
	redFlash = true;
	UpdateHealth(-Damage);
	DamageTimer();
}

void AWitch::UpdateMagic()
{
	PreviousMagic = MagicPercentage;
	MagicPercentage = Magic / FullMagic;
	MagicValue = 1.0f;
	if (MyTimeline != nullptr) MyTimeline->PlayFromStart();
}

void AWitch::SetMagicChange(float MagicChange)
{
	bCanUseMagic = false;
	PreviousMagic = MagicPercentage;
	MagicValue = (MagicChange / FullMagic);

	if (GunOverheatMaterial) Magic_Point->SetMaterial(0, GunOverheatMaterial);

	if (MyTimeline != nullptr) MyTimeline->PlayFromStart();
}