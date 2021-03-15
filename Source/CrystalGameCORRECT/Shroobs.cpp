// Fill out your copyright notice in the Description page of Project Settings.


#include "Shroobs.h"

// Sets default values
AShroobs::AShroobs()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AShroobs::BeginPlay()
{
	Super::BeginPlay();

	FVector Steps(0.0, 100.0, 0.0);
	AShroobs::AddActorLocalOffset(Steps, false, nullptr);
	
	
}

// Called every frame
void AShroobs::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Steps{ (float)sin(AShroobs::GetGameTimeSinceCreation()) * 500, 0.0, 0.0 };
	AShroobs::AddActorLocalOffset(Steps * DeltaTime, true, nullptr);


	/*FVector CurrentLocation = GetActorLocation();
	CurrentLocation += GetActorForwardVector() * MoveSpeed * DeltaTime;
	SetActorLocation(CurrentLocation);*/

}

