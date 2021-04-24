// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CrystalProjectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class CRYSTALGAMECORRECT_API ACrystalProjectile : public AActor
{
	GENERATED_BODY()
	
private:

	//Adding the meshes and projectile movement to the Projectile
	//We add the actual mesh to the projectile inside the engine
	UPROPERTY(EditAnywhere, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(EditAnywhere, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(EditAnywhere, Category = "Damage")
		TSubclassOf<UDamageType> DamageType;
	//Movement speed and damage
	//Both editable in the engine
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move", meta = (AllowPrivateAccess = "true"))
		float MovementSpeed = 1500;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
		float Damage = 50;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Sets default values for this actor's properties
	ACrystalProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
