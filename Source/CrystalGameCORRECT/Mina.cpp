// Fill out your copyright notice in the Description page of Project Settings.


#include "Mina.h"
#include <Components/InputComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"


// Sets default values
AMina::AMina()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	

	//Put this code in APlayer::APlayer() function
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 500.f;//how far away form character
	SpringArmComp->SetRelativeRotation(FRotator(-30.f, 10.f, 0.f));//Rotation relative to character

	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 10.f;//change this to get more or less camera lag
	SpringArmComp->bDoCollisionTest = false;


	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	Jumping = false;

	//Set turn rate 
	BaseTurnRate = 20.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	////Character rotation
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(500.0f, 0.0f, 0.0f);


	//Jump Height and Character control in the air
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 20.0f;

	//dashing values
	CanDash = true;
	DashDistance = 6000.f;
	DashCooldown = 1.f;
	DashStop = 0.1f;

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

	
}

// Called to bind functionality to input
void AMina::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &AMina::Forward);
	PlayerInputComponent->BindAxis("Right", this, &AMina::Right);
	PlayerInputComponent->BindAxis("CameraTurn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("CharacterRot", this, &AMina::TurnAtRate);

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

void AMina::Dash()
{
	if (CanDash)
	{
		GetCharacterMovement()->BrakingFrictionFactor = 0.f;
		LaunchCharacter(FVector(CameraComp->GetForwardVector().X, CameraComp->GetForwardVector().Y, 0).GetSafeNormal() * DashDistance, true, true);
		CanDash = false;
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &AMina::StopDashing, DashStop, false);
	}
}

void AMina::StopDashing()
{
	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->BrakingFrictionFactor = 2.f;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AMina::ResetDash, DashCooldown, false);
}

void AMina::ResetDash()
{
	CanDash = true;

}

void AMina::TurnAtRate(float Rate)
{
	// Calculate delta for the first frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMina::Forward(float Value)
{
	if (Value != 0.0f)
	{
		// used to find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get the forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
	
	
	/*if (Value)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}*/
}

void AMina::Right(float Value)
{

	if (Value != 0.0f)
	{
		// used to find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get the forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}

	/*if (Value)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}*/
}

