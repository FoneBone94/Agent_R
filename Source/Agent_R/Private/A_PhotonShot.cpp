#include "A_PhotonShot.h"

// Sets default values for this component's properties
UA_PhotonShot::UA_PhotonShot()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UA_PhotonShot::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UA_PhotonShot::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...
}

