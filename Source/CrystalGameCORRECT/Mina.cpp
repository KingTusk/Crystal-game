// Fill out your copyright notice in the Description page of Project Settings.


#include "Mina.h"

// Sets default values
AMina::AMina()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	Jumping = false;

}

void AMina::Dash()
{

}

// Called when the game starts or when spawned
void AMina::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMina::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Jumping)
	{
		Jump();
	}

	CanDash = true;
	DashDistance = 6000.f;
	DashCooldown = 1.f;
	DashStop = 0.1f;
}

// Called to bind functionality to input
void AMina::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &AMina::Forward);
	PlayerInputComponent->BindAxis("Right", this, &AMina::Right);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMina::CheckJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMina::CheckJump);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AMina::Dash);

}

void AMina::CheckJump()
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

void AMina::Forward(float Value)
{
	if (Value)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AMina::Right(float Value)
{
	if (Value)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

