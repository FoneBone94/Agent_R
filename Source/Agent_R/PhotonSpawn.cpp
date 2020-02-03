#include "PhotonSpawn.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UPhotonSpawn::UPhotonSpawn()
{
	// Set this component to be initialized when the game starts
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

//spawns and projects an object forward
void UPhotonSpawn::SpawnPhoton()
{
	FActorSpawnParameters SpawnParams;
	AActor* SpawnActorRef = GetWorld()->SpawnActor<AActor>(SpawnParams);
}

// Called when the game starts
void UPhotonSpawn::BeginPlay()
{
	//Super::BeginPlay();
	
	// ...
	
}


// Called every frame
void UPhotonSpawn::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...
}

