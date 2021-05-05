// The game and source code belongs to Team 7 Programming team


#include "Pickup.h"
#include "Health.h"
#include "Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Ammo = false;

	Health = false;

	//Rootcomponent
	PickupRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootPickup"));
	RootComponent = PickupRoot;

	//Mesh Component
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshPickup"));
	PickupMesh->SetupAttachment(PickupRoot);

	PickupBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxPickup"));
	PickupBox->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	PickupBox->SetGenerateOverlapEvents(true);
	PickupBox->SetupAttachment(PickupRoot);

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
	PickupBox->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnPlayerEnterPickupBox);
	/*CrystalProjectile = Cast<ACrystalProjectile::CrystalAmmo>*/
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickup::OnPlayerEnterPickupBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	UE_LOG(LogTemp, Warning, TEXT("Object Picked up"))
	if (Ammo == true)
	{
		AmmoRefill();
		Destroy();
	}
	
	if (Health == true)
	{
		HealthRefill();
		Destroy();
	}
	
}

void APickup::AmmoRefill()
{
	UE_LOG(LogTemp, Warning, TEXT("Ammo refilled"))
		
}

void APickup::HealthRefill()
{
	UE_LOG(LogTemp, Warning, TEXT("Health Refilled"))
}

