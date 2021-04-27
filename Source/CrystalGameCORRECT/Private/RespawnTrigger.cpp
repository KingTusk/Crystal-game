// The game and source code belongs to Team 7 Programming team


#include "RespawnTrigger.h"
#include "DrawDebugHelpers.h"


ARespawnTrigger::ARespawnTrigger()
{
	OnActorBeginOverlap.AddDynamic(this, &ARespawnTrigger::OnOverLapBegin);
	OnActorEndOverlap.AddDynamic(this, &ARespawnTrigger::OnOverlapEnd);
	SpawnPoint = false;
}


void ARespawnTrigger::BeginPlay()
{
	Super::BeginPlay();

	//drawing the outlines of the box
	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Red, true, -1, 0, 5);
	

}


//What happens when a player enters the trigger volume
void ARespawnTrigger::OnOverLapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		UE_LOG(LogTemp, Warning, TEXT("Respawn point triggered"))
			SpawnPoint = true;
	}
}

//What happens when a player exits the trigger
void ARespawnTrigger::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		UE_LOG(LogTemp, Warning, TEXT("Left respawn trigger"))
	}
}