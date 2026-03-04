// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUps/HealthPickup.h"
#include "HealthPickUpSpawner.generated.h"

UCLASS()
class VGP201_API AHealthPickUpSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthPickUpSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AHealthPickup> PickupClass;

	UPROPERTY(EditAnywhere)
	float SpawnInterval = 120.0f;

	UPROPERTY()
	AHealthPickup* CurrentPickup;	//For keeping track of the current pickup, so we can check if it's been picked up or not

	UFUNCTION()
	void OnPickupDestroyed(AActor* DestroyedActor);

	FTimerHandle SpawnTimerHandle;

	void SpawnPickup();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
