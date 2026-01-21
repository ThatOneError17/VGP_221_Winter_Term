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
}



