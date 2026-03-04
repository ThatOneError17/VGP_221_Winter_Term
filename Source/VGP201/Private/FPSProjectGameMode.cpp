// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProjectGameMode.h"


void AFPSProjectGameMode::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	//1. Print to Screen
	// Display a debug message for five seconds. 
	// The -1 "Key" value argument prevents the message from being updated or refreshed.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameModeBase! This is hybrid Build"));

	//2. Print to Output Log
	UE_LOG(LogTemp, Warning, TEXT("Helllo World"));	//Doesn't seem to be working

	//3. Printing values to output log
	int TestNumber = 42;
	bool TestBool = true;
	UE_LOG(LogTemp, Warning, TEXT("TestNumber: %i"), TestNumber);
	UE_LOG(LogTemp, Warning, TEXT("TestBool: %i"), TestBool);

	int* TestNumberPtr = &TestNumber;
	UE_LOG(LogTemp, Warning, TEXT("TestNumberPtr: %p"), TestNumberPtr);
	UE_LOG(LogTemp, Warning, TEXT("TestNumberPtr: %i"), TestNumberPtr);
	UE_LOG(LogTemp, Warning, TEXT("TestNumberPtr DeRef: %i"), *TestNumberPtr);

	FString TestString = TEXT("This is a test string");
	UE_LOG(LogTemp, Warning, TEXT("TestString: %s"), *TestString);

	// 4. Modern way of debugging values
	UE_LOGFMT(LogTemp, Warning, "TestNumber: {0}, TestBool{1}, TestString{2}", TestNumber, TestBool, "TestString");

	AGameHUD* HUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<AGameHUD>();	//Need to fix
	HUD->GameMenuWidgetContainer->SetScoreText(0);
	HUD->GameMenuWidgetContainer->SetTimerText(0);

	//Get player character and bind to death event
	AFPSCharacter* Player = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (Player) 
	{
		Player->OnPlayerDied.AddDynamic(this, &AFPSProjectGameMode::HandlePlayerDied);
	}

	GetWorldTimerManager().SetTimer(GameTimerHandle, this, &AFPSProjectGameMode::UpdateGameTimer, 1.0f, true);	//UpdateGameTimer will be called every second (1.0f) and will loop 
}

void AFPSProjectGameMode::HandlePlayerDied()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Died!"));
	TArray<AActor*> FoundSpawners;	//Gets all enemy spawners in the level and stops them from spawning more enemies when the player dies
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawner::StaticClass(), FoundSpawners);

	for (AActor* Actor : FoundSpawners)
	{
		AEnemySpawner* Spawner = Cast<AEnemySpawner>(Actor);
		if (Spawner)
		{
			Spawner->StopSpawning();	//Calls the StopSpawning function
		}
	}

	GoToGameOver();
}

void AFPSProjectGameMode::HandleEnemyDied(AEnemyAICharacter* Enemy)
{
	UpdateScore(10);	//Update the score by 10 points when an enemy dies
}

void AFPSProjectGameMode::GoToGameOver()
{
	UE_LOG(LogTemp, Warning, TEXT("Going to Game Over Screen"));
	UGameplayStatics::OpenLevel(this, FName("GameOver"));
}

void AFPSProjectGameMode::GoToMainMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("Going to Main Menu"));
	UGameplayStatics::OpenLevel(this, FName("MainMenu"));
}

void AFPSProjectGameMode::UpdateGameTimer()
{
	ElapsedTime++;

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!PC) return;

	AGameHUD* HUD = PC->GetHUD<AGameHUD>();
	if (!HUD) return;

	if (HUD->GameMenuWidgetContainer)
	{
		HUD->GameMenuWidgetContainer->SetTimerText(ElapsedTime);
	}
}

void AFPSProjectGameMode::UpdateScore(int ScoreAmount)	//Updates the score text in the HUD when an enemy dies, and is called from HandleEnemyDied
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!PC) return;

	AGameHUD* HUD = PC->GetHUD<AGameHUD>();
	if (!HUD) return;

	if(HUD->GameMenuWidgetContainer)
	{
		HUD->GameMenuWidgetContainer->SetScoreText(ScoreAmount);
	}
}






