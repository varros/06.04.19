// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class WITCH_HUNT_API AProjectile : public AActor
{
	GENERATED_BODY()
	
	//Sphere collision
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class USphereComponent* CollisionComponent;

	//Projectile movement
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//If projectile hits something
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Returns CollisionComponent
	FORCEINLINE class USphereComponent* GetCollisionComponent() const { return CollisionComponent; }
	//Returns ProjectileMovement
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

private:
	UPROPERTY(EditAnywhere, Category = "Damage")
		float Projectiledamage = 20.f;

	UPROPERTY(EditAnywhere, Category = "Radius")
		float Radius = 5.f;

};
