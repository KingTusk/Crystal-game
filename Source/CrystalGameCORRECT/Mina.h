// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Mina.generated.h"

class ACrystalProjectile;

UCLASS()
class CRYSTALGAMECORRECT_API AMina : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMina();

	//Components for Mina
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArmComp;
	UPROPERTY(EditAnywhere)
	class UCameraComponent* CameraComp;

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<ACrystalProjectile> ProjectileClass;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Projectile");
	USceneComponent* ProjectileSpawnPoint;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* AttackBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
		FVector AttackPlacement {70.f, 0.f, 35.f};


	//Mina turning speed
    UPROPERTY(EditAnywhere, Category = "MinaTurning")
		float BaseTurnRate;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void Refill();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	FORCEINLINE class UCameraComponent* GetCameraComp() const { return CameraComp; }


	//Movng forward
	UFUNCTION()
		void Forward(float Value);
	//Moving right
	UFUNCTION()
		void Right(float Value);

	//Called via input to turn at a a given rate
	UFUNCTION()
		void TurnAtRate(float Rate);

	//Jumpong Functions
	UFUNCTION()
		void CheckJump();
	UPROPERTY()
		bool Jumping;

	//Mellee attacks and projectile attacks below
	UFUNCTION()
		void Melee();
	UFUNCTION()
		void StopMelee();

	//We dont have a attack animation for the game yet, once that is implemented we can remove this boolean
	bool isAttacking{ false };
	FVector temp{ 1.f };

	UPROPERTY()
		float Damage;
	UFUNCTION()
		void Shoot();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
		int32 CrystalAmmo { 0 };

	//Dash Functions and porperty
	//Length of desh, speed of dash, dash stop timer etc.
	UFUNCTION()
		void Dash();
	UPROPERTY(EditAnywhere)
		float DashDistance;
	UPROPERTY(EditAnywhere)
		float DashCooldown;
	UPROPERTY()
		bool CanDash;
	UPROPERTY(EditAnywhere)
		float DashStop;
	UPROPERTY()
		FTimerHandle UnusedHandle;
	UFUNCTION()
		void StopDashing();
	UFUNCTION()
		void ResetDash();
};
