// The game and source code belongs to Team 7 Programming team


#include "OutOfBoundTrigger.h"
#include "DrawDebugHelpers.h"


AOutOfBoundTrigger::AOutOfBoundTrigger()
{
	OnActorBeginOverlap.AddDynamic(this, &AOutOfBoundTrigger::OnOverLapBegin);
	OnActorEndOverlap.AddDynamic(this, &AOutOfBoundTrigger::OnOverlapEnd);
}


void AOutOfBoundTrigger::BeginPlay()
{
	Super::BeginPlay();

	//Drawing the box in the world so i can see where the bounds are
	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);

}

//What happens when player enters the trigger volume
void AOutOfBoundTrigger::OnOverLapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this) && SpecificActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap has begun"))
		
	}
	else if(OtherActor && (OtherActor != this)  && !SpecificActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unrecognised actor"))
	}
}

//What happens when player exits the trigger wolume
void AOutOfBoundTrigger::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this) && SpecificActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap has ended"))
	}
	else if(OtherActor && (OtherActor != this) && !SpecificActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unrecognised actor"))
	}

}