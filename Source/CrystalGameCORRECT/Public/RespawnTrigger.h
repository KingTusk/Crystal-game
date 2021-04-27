// The game and source code belongs to Team 7 Programming team

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "OutOfBoundTrigger.h"
#include "RespawnTrigger.generated.h"




/**
 * 
 */
UCLASS()
class CRYSTALGAMECORRECT_API ARespawnTrigger : public ATriggerBox
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

public:

	ARespawnTrigger();

	UFUNCTION()
		void OnOverLapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
		void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

	UPROPERTY()
		bool SpawnPoint;

};
