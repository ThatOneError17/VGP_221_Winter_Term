// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/EnemySpawner.h"
#include "GameFramework/GameModeBase.h"
#include "GameHUD.h"
#include "Logging/StructuredLog.h"	
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"
#include "FPSProjectGameMode.generated.h"

/**
 * 
 */
UCLASS()
class VGP201_API AFPSProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	virtual void StartPlay() override;

	UFUNCTION()
	void HandlePlayerDied();



	UFUNCTION()
	void GoToGameOver();

public:
	UFUNCTION()
	void GoToMainMenu();

	UFUNCTION()
	void HandleEnemyDied(AEnemyAICharacter* Enemy);

	FTimerHandle GameTimerHandle;	

	int32 ElapsedTime = 0;

	UFUNCTION()
	void UpdateGameTimer();

	UFUNCTION()
	void UpdateScore(int ScoreAmount);
};
