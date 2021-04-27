// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shroobs.generated.h"

UCLASS()
class CRYSTALGAMECORRECT_API AShroobs : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShroobs();
	
	void ImHit();

protected:

	

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* ShroobCollider;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* ShroobVisibleMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
