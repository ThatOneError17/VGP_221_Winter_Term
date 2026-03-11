// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/EnemySpawner.h"
#include "GameFramework/Actor.h"
#include "PressurePlate.h"
#include "Door.generated.h"


UCLASS()
class VGP201_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

	UFUNCTION()
	void DestroyDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Door")
	TArray<class APressurePlate*> PressurePlates;	//Array of pressure plates that need to be stepped on to open the door

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Door")	//Can apply spawners in details
	AEnemySpawner* LinkedSpawner;

	UFUNCTION()	//Checks if all pressure plates are active, and if so, destroys the door and therefore enables linked spawner
	void CheckPlates();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
