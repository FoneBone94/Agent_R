// Fill out your copyright notice in the Description page of Project Settings.


#include "A_MegaLazer.h"

// Sets default values for this component's properties
UA_MegaLazer::UA_MegaLazer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UA_MegaLazer::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UA_MegaLazer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

