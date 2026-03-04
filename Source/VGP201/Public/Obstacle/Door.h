// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/EnemySpawner.h"
#include "GameFramework/Actor.h"
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

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Door")	//Can apply spawners in details
	AEnemySpawner* LinkedSpawner;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
