


#include "PhotonSpawn_A.h"

// Sets default values for this component's properties
UPhotonSpawn_A::UPhotonSpawn_A()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPhotonSpawn_A::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPhotonSpawn_A::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

