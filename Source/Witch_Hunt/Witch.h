// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Witch.generated.h"

class UInputComponent;
class UTimelineComponent;

UCLASS()
class WITCH_HUNT_API AWitch : public ACharacter
{
	GENERATED_BODY()

		/** Gun mesh: 1st person view (seen only by self) */
		UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* Magic_Point;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USceneComponent* Magic_PointLocation;

public:
	// Sets default values for this character's properties
	AWitch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MagicOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* FireAnimation;


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* Character movement */
	void MoveRight(float value);
	void MoveForward(float value);
	void Jump();
	void StopJump();
	void Fire();

	// Returns TopDownCameraComponent
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	// Returns CameraBoom subobject
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float FullHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float HealthPercentage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float FullMagic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
		float Magic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
		float MagicPercentage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
		float PreviousMagic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
		float MagicValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		bool redFlash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
		UCurveFloat* MagicCurve;

	float CurveFloatValue;
	float TimelineValue;
	bool bCanUseMagic;

	UTimelineComponent* MyTimeline;
	struct FTimerHandle MemberTimerHandle;
	struct FTimerHandle MagicTimerHandle;

	/** Get Health */
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealth();

	/** Get Magic */
	UFUNCTION(BlueprintPure, Category = "Magic")
		float GetMagic();

	/** Get Health Text */
	UFUNCTION(BlueprintPure, Category = "Health")
		FText GetHealthIntText();

	/** Get Magic Text */
	UFUNCTION(BlueprintPure, Category = "Magic")
		FText GetMagicIntText();

	/** Damage Timer */
	UFUNCTION()
		void DamageTimer();

	/** Set Damage State */
	UFUNCTION()
		void SetDamageState();

	/** Set Magic Value */
	UFUNCTION()
		void SetMagicValue();

	/** Set Damage State */
	UFUNCTION()
		void SetMagicState();

	/** Set Damage State */
	UFUNCTION()
		void SetMagicChange(float MagicChange);

	/** Set Damage State */
	UFUNCTION()
		void UpdateMagic();

	/** Play Flash */
	UFUNCTION(BlueprintPure, Category = "Health")
		bool PlayFlash();

	UPROPERTY(EditAnywhere, Category = "Magic")
		class UMaterialInterface* GunDefaultMaterial;

	UPROPERTY(EditAnywhere, Category = "Magic")
		class UMaterialInterface* GunOverheatMaterial;

	// void ReceivePointDamage(float Damage, const class UDamageType * DamageType, FVector HitLocation, FVector HitNormal, class UPrimitiveComponent * HitComponent, FName BoneName, FVector ShotFromDirection, class AController * InstigatedBy, AActor * DamageCauser, const FHitResult & HitInfo);

	UFUNCTION(BlueprintCallable, Category = "Power")
		void UpdateHealth(float HealthChange);

	void ReceivePointDamage(float Damage, const class UDamageType * DamageType, FVector HitLocation, FVector HitNormal, class UPrimitiveComponent * HitComponent, FName BoneName, FVector ShotFromDirection, class AController * InstigatedBy, AActor * DamageCauser, const FHitResult & HitInfo);


private:

	// Top down camera 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TopDownCameraComponent;

	// Camera boom positioning the camera above the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

};
