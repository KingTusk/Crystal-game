// The game and source code belongs to Team 7 Programming team

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "RespawnTrigger.h"
#include "OutOfBoundTrigger.generated.h"


class AMina;

UCLASS()
class CRYSTALGAMECORRECT_API AOutOfBoundTrigger : public ATriggerBox
{
	GENERATED_BODY()

protected:
	
	virtual void BeginPlay() override;

public:

	AOutOfBoundTrigger();

	UFUNCTION()
		void OnOverLapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
		void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

	UPROPERTY(EditAnywhere)
		class AMina* SpecificActor;

	
};
