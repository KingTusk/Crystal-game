// Fill out your copyright notice in the Description page of Project Settings.


#include "Mina.h"
#include <Components/InputComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "CrystalProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Shroobs.h"
#include "Health.h"


// Sets default values
AMina::AMina()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// set our turn rates for input
	BaseTurnRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; 	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 20.0f;
	
	// Create a camera boom
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 1200.0f; // The camera follows at this distance behind the character	
	SpringArmComp->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 10.f;
	SpringArmComp->bDoCollisionTest = false;
	CameraComp->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnComp"));
	ProjectileSpawnPoint->SetupAttachment(RootComponent);

	//Simple melee attack box - this should eventually be put on a socket on the skeleton of the player to follow the attack-animation
	AttackBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PlayerAttack"));
	AttackBox->InitBoxExtent(FVector(30.f, 30.f, 30.f));
	AttackBox->SetupAttachment(RootComponent);
	AttackBox->SetGenerateOverlapEvents(false);
	AttackBox->SetRelativeLocation(AttackPlacement);


	//dashing values
	CanDash = true;
	DashDistance = 4000.f;
	DashCooldown = 1.f;
	DashStop = 0.2f; 
    Jumping = false;
}


// Called when the game starts or when spawned
void AMina::BeginPlay()
{
	Super::BeginPlay();

	AttackBox->OnComponentBeginOverlap.AddDynamic(this, &AMina::OnOverlap);
	
}

// Called every frame
void AMina::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Jumping)
	{
		Jump();
	}
	//Only temporary as we have no attack animation
	if (isAttacking)
	{
		//Move the hitbox to trigger the overlap event
		AttackBox->SetRelativeLocation(AttackPlacement + temp);
		temp *= -1.f;
	}
	
}

// Called to bind functionality to input
void AMina::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	//Player forward and right movement 
	PlayerInputComponent->BindAxis("Forward", this, &AMina::Forward);
	PlayerInputComponent->BindAxis("Right", this, &AMina::Right);

	PlayerInputComponent->BindAxis("CameraRotate", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("CharacterRot", this, &AMina::TurnAtRate);

	//Actions inputs
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMina::CheckJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMina::CheckJump);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AMina::Dash);
	PlayerInputComponent->BindAction("Melee", IE_Pressed, this, &AMina::Melee);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMina::Shoot);
	PlayerInputComponent->BindAction("Melee", IE_Released, this, &AMina::StopMelee);
	//PlayerInputComponent->BindAction("Shoot", IE_Released, this, &AMina::Shoot);

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
		LaunchCharacter(FVector(RootComponent->GetForwardVector().X, RootComponent->GetForwardVector().Y, 0).GetSafeNormal() * DashDistance, true, true);
		CanDash = false;
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &AMina::StopDashing, DashStop, false);
	}
}

void AMina::Melee()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack"));
	AttackBox->SetGenerateOverlapEvents(true);
	isAttacking = true;	//only needed until we get animation

}

void AMina::StopMelee()
{
	UE_LOG(LogTemp, Warning, TEXT("Stop Attack"));
	AttackBox->SetGenerateOverlapEvents(false);
	isAttacking = false;	//only needed until we get animation
}

void AMina::OnOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
	UE_LOG(LogTemp, Warning, TEXT("Enemy Overlaps %s"), *OtherActor->GetName())
	if (OtherActor->IsA(AShroobs::StaticClass()))
	{
		Cast<AShroobs>(OtherActor)->ImHit();
		CrystalAmmo++;
	}
}


void AMina::Shoot()
{
	if (CrystalAmmo > 0)
	{
		//Spawning the projectile and determining if its hit the enemy and killed them
		if (ProjectileClass)
		{
			FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
			FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

			ACrystalProjectile* TempProjectile = GetWorld()->SpawnActor<ACrystalProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
			TempProjectile->SetOwner(this);
			CrystalAmmo--;
		}
	}

}

void AMina::HandleDestruction()
{


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

void AMina::BeginOverlap()
{
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

}

