// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Mina.generated.h"

UCLASS()
class CRYSTALGAMECORRECT_API AMina : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMina();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MinaTurning")
		float BaseTurnRate;

	UPROPERTY(EditAnywhere);
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere);
	class UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* AttackBox;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

	/*UFUNCTION()
	void BeginOverlap();*/
};
