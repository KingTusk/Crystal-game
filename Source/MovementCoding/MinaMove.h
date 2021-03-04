// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InputComponent.h"
#include "GameFramework/Character.h"
#include "MinaMove.generated.h"

UCLASS()
class MOVEMENTCODING_API AMinaMove : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMinaMove();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	//movement for Mina
	void Forward(float Value);
	void Right(float Value);

	void CheckJump();

	UPROPERTY()
		bool Jumping;
};
