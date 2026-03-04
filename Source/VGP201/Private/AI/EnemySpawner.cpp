// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EnemySpawner.h"
#include "FPSProjectGameMode.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();


    if (EnemyClass && bSpawnerEnabled)
    {
		GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemySpawner::SpawnEnemy, SpawnInterval, true);    //Sets a timer to call SpawnEnemy every SpawnInterval seconds
    }

	
}

void AEnemySpawner::SpawnEnemy()    //Spawns an enemy at the spawner's location and rotation
{
    if (!EnemyClass) return;


    FVector SpawnLocation = GetActorLocation(); 
    FRotator SpawnRotation = GetActorRotation();

    AEnemyAICharacter* Enemy = GetWorld()->SpawnActor<AEnemyAICharacter>(EnemyClass, SpawnLocation, SpawnRotation); //Sets a timer to call SpawnEnemy every SpawnInterval seconds


    if (Enemy)
    {
        AFPSProjectGameMode* GM = Cast<AFPSProjectGameMode>(GetWorld()->GetAuthGameMode());
        if (GM)
        {
            Enemy->OnEnemyDied.AddDynamic(GM, &AFPSProjectGameMode::HandleEnemyDied);
        }
    }
}

void AEnemySpawner::SetSpawnerEnabled(bool bEnabled)
{
    bSpawnerEnabled = bEnabled;

    if (bSpawnerEnabled)
    {
        //Start timer
        if (!GetWorld()->GetTimerManager().IsTimerActive(SpawnTimerHandle))
        {
            GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemySpawner::SpawnEnemy, SpawnInterval, true);
        }
    }
    else
    {
        //Stop timer
        GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
    }
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

