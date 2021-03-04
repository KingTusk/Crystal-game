// Fill out your copyright notice in the Description page of Project Settings.


#include "MinaMove.h"

// Sets default values
AMinaMove::AMinaMove()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	Jumping = false;
}

// Called when the game starts or when spawned
void AMinaMove::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMinaMove::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Jumping)
	{
		Jump();
	}

}

// Called to bind functionality to input
void AMinaMove::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &AMinaMove::Forward);
	PlayerInputComponent->BindAxis("Right", this, &AMinaMove::Right);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMinaMove::CheckJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMinaMove::CheckJump);

}

void AMinaMove::CheckJump() 
{
	if (Jumping)
	{
		Jumping = false;
	}
	else
	{
		Jumping = true;
	}
}

void AMinaMove::Forward(float Value)
{
	if (Value)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AMinaMove::Right(float Value) 
{
	if (Value)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

