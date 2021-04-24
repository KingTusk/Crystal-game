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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* AttackBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Type", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ACrystalProjectile> ProjectileClass;

	//Mina turning speed
    UPROPERTY(EditAnywhere, Category = "MinaTurning")
		float BaseTurnRate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void HandleDestruction();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:

	//Movng forward
	void Forward(float Value);

	//Moving right
	void Right(float Value);

	//Called via input to turn at a a given rate
	void TurnAtRate(float Rate);

	void CheckJump();

	UPROPERTY()
		bool Jumping;

	UFUNCTION()
		void Dash();

	UFUNCTION()
		void Melee();

	UPROPERTY(EditAnywhere)
	int CrystalAmmo = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRange = 500.0f;

	void CheckShootCondition();

	float ReturnDistanceToPlayer();

	FTimerHandle FireRateTimerHandle;

	AMina *MinaPlayer;

	UFUNCTION()
		void Shoot();

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

	UFUNCTION()
	void BeginOverlap();

public:
	FORCEINLINE class UCameraComponent* GetCameraComp() const { return CameraComp; }
};
