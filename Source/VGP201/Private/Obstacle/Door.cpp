// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle/Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ADoor::DestroyDoor()
{
	//Need to add code to enable a spawner that might be connected to a door, so that when the door is destroyed, the spawner starts spawning enemies
	if (LinkedSpawner)
	{
		LinkedSpawner->SetSpawnerEnabled(true);
	}
	Destroy();
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	for (APressurePlate* Plate : PressurePlates)	//For each pressure plate in the array, add a dynamic delegate to the OnPlateStateChanged event, so that when the event is triggered, the CheckPlates function is called
	{
		if (Plate)
		{
			Plate->OnPlateStateChanged.AddDynamic(this, &ADoor::CheckPlates);
		}
	}
	
}

void ADoor::CheckPlates()
{
	for (APressurePlate* Plate : PressurePlates)	//For each pressure plate in the array, check if it's active. If any of them are not active, return and do not destroy the door
	{
		if (!Plate || !Plate->bIsActive)
		{
			return;
		}
	}

	DestroyDoor();
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

