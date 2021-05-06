// Fill out your copyright notice in the Description page of Project Settings.


#include "Shroobs.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Health.h"

// Sets default values
AShroobs::AShroobs()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up the collider for the shroob
	ShroobCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("ShroobCollider"));
	ShroobCollider->InitBoxExtent(FVector(50.f));

	// Set OurCollider to be the RootComponent
	RootComponent = ShroobCollider;

	// Set up our visible mesh
	ShroobVisibleMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShroobVisibleMesh"));
	ShroobVisibleMesh->SetupAttachment(RootComponent);
	

}

// Called when the game starts or when spawned
void AShroobs::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AShroobs::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShroobs::ImHit()
{
	/*if (Health <= 0)
	{*/
		//Destroys the Shroob
		Destroy();
	/*}*/
	
}

