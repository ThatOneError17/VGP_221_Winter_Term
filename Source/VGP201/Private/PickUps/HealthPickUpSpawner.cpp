// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUps/HealthPickUpSpawner.h"

// Sets default values
AHealthPickUpSpawner::AHealthPickUpSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AHealthPickUpSpawner::BeginPlay()
{
	Super::BeginPlay();
    SpawnPickup();
	
}

void AHealthPickUpSpawner::OnPickupDestroyed(AActor* DestroyedActor)
{
    CurrentPickup = nullptr;

	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AHealthPickUpSpawner::SpawnPickup, SpawnInterval, false);  //Spawn a new pickup after the specified interval
}

void AHealthPickUpSpawner::SpawnPickup()
{
    if (!PickupClass || CurrentPickup) return;

    FVector SpawnLocation = GetActorLocation();
    FRotator SpawnRotation = GetActorRotation();

    CurrentPickup = GetWorld()->SpawnActor<AHealthPickup>(PickupClass, SpawnLocation, SpawnRotation);

    if (CurrentPickup)
    {
        CurrentPickup->OnDestroyed.AddDynamic(this, &AHealthPickUpSpawner::OnPickupDestroyed);
    }
}

// Called every frame
void AHealthPickUpSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

