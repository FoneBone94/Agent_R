

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Photon.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AGENT_R_API UPhoton : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPhoton();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void dealdamage();
	int Damage = 1;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
