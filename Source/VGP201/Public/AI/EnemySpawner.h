// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI/EnemyAICharacter.h"
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "EnemySpawner.generated.h"

class AFPSProjectGameMode;

UCLASS()
class VGP201_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    // Enemy to spawn
    UPROPERTY(EditAnywhere, Category = "Spawning")
    TSubclassOf<AActor> EnemyClass;

    // Time between spawns
    UPROPERTY(EditAnywhere, Category = "Spawning")
    float SpawnInterval = 6.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")  //Whether the spawner is enabled or not
    bool bSpawnerEnabled = true;


    // Timer handle
    FTimerHandle SpawnTimerHandle;

    // Spawn function
    UFUNCTION()
    void SpawnEnemy();

   



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Spawning")
    void SetSpawnerEnabled(bool bEnabled);  //Enables or disables the spawner, starting or stopping the spawn timer as needed

    void StopSpawning()    //Stops the spawning timer
    {
        GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
	}

};
