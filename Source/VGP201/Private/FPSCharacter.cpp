// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UE_LOG(LogTemp, Warning, TEXT("FPSCharacter Constructor Called"));

	//This is a crash test
	//int* CrashInt = nullptr;

	//UE_LOG(LogTemp, Warning, TEXT("%i"), *CrashInt);
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::OnMoveRight);

	PlayerInputComponent->BindAxis("LookHorizontal", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookVertical", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::EndJump);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);
}
	

void AFPSCharacter::OnMoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AFPSCharacter::OnMoveRight(float Value)
{
	// Finish Move Right
	FVector Direction = GetActorRightVector();
	AddMovementInput(Direction, Value);
}

void AFPSCharacter::StartJump()
{
	// Have the character jump without usign Character::Jump()
	bPressedJump = true;
}

void AFPSCharacter::EndJump()
{
	bPressedJump = false;
}

void AFPSCharacter::Fire()
{
	// Print a console message for fire
	UE_LOG(LogTemp, Warning, TEXT("FIRE"));
}

